//Replacer.cpp
/*
* ���ϸ�Ī:Replacer.cpp
* ���:ã��� �ٲٱ� ������ ����Ѵ�.
* �ۼ���:������
* �ۼ�����:2022/12/7
*/
#include "Replacer.h"
#include "Finder.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "MacroCommand.h"
#include "Select.h"

#include "GlyphCreater.h"
#include "Paper.h"
#include "Line.h"
#include "resource.h"
#include <afxdlgs.h>

/*
* �Լ���Ī:Replacer
* ���:������
*/
Replacer::Replacer(Notepannel* notepannel, string find, string replace)
	:notepannel(notepannel), replace(replace) {
	this->replaceAll = 0;
	this->replaceCurrent = 0;
	this->paperToReplace = 0;

	GlyphCreater glyphCreater;
	

	Glyph* line = 0;
	if (this->replace != "") {
		this->paperToReplace = glyphCreater.Create(this->replace);
	}
	else {
		this->paperToReplace = glyphCreater.Create("");
		line = glyphCreater.Create("\r\n");
		this->paperToReplace->Add(line);
	}

}
Replacer::Replacer(Notepannel* notepannel, WPARAM wParam, LPARAM lParam) : notepannel(notepannel) {
	CFindReplaceDialog* cFindReplaceDialog = CFindReplaceDialog::GetNotifier(lParam);
	//�ٲٱ⸦ ���� ����
	this->replace = (LPCSTR)(cFindReplaceDialog->GetReplaceString());
	this->replaceAll = cFindReplaceDialog->ReplaceAll();
	this->replaceCurrent = cFindReplaceDialog->ReplaceCurrent();
	this->paperToReplace = 0;

	GlyphCreater glyphCreater;

	Glyph* line = 0;
	if (this->replace != "") {
		this->paperToReplace = glyphCreater.Create(this->replace);
	}
	else {
		this->paperToReplace = glyphCreater.Create("");
		line = glyphCreater.Create("\r\n");
		this->paperToReplace->Add(line);
	}
}

/*
* �Լ���Ī:~Replacer
* ���:�Ҹ���
*/
Replacer::~Replacer() {
	delete paperToReplace;
}

/*
* �Լ���Ī:ReplaceCurrent
* ���:���� ���õ� ������ �ٲ� �������� �ٲ۴�. 
*/
void Replacer::ReplaceCurrent() {
	CommandCreator commandCreater(this->notepannel);
	Command* command = NULL;
	Glyph* currentLine = 0;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long frontLineOrder;
	Long frontCharIndex;
	Long endLineOrder;
	Long endCharIndex;


	frontLineOrder = this->notepannel->select->frontLineOrder;
	frontCharIndex = this->notepannel->select->frontXIndex;


	//���õ� ������ �����Ѵ�. 
	command = commandCreater.Create(IDM_FORMAT_DELETE);
	if (command != NULL) {
		command->Execute();
		this->notepannel->macroCommand->Add(command, 0);
		command = NULL;
	}
	//���� ��ġ�� �ٲ� ������ ���δ�. 
	command = commandCreater.Create(IDM_FORMAT_PASTE, this->paperToReplace);
	if (command != NULL) {
		command->Execute();
		this->notepannel->macroCommand->Add(command, 1); //��ũ�� �÷��׸� �ø���. 
	}
	this->notepannel->paper->MergeAllDummyLines();

	Long replacePaperLength = this->paperToReplace->GetLength();
	Long replacePaperEndLineLength;

	endLineOrder = frontLineOrder + replacePaperLength - 1;
	currentLine = this->paperToReplace->GetAt(paperToReplace->Last());
	replacePaperEndLineLength = currentLine->GetLength();
	if (replacePaperLength <= 1) {
		endCharIndex = frontCharIndex + replacePaperEndLineLength;
	}
	else {
		endCharIndex = replacePaperEndLineLength - 1;
	}


	//�˻����⿡ �°� ���� ��ġ�� �����Ѵ�. 

	if (this->notepannel->finder->searchDown == TRUE) { //ã�� ������ �Ʒ���
		//������ ��ġ�� ������ ��ġ�� �̵��Ѵ�.
		lineOrder = this->notepannel->paper->Move(endLineOrder);
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		charIndex = currentLine->Move(endCharIndex);
	}
	else { //ã�� ������ ���̸�
		//������ ��ġ�� �������� �̵��Ѵ�. 
		lineOrder = this->notepannel->paper->Move(frontLineOrder);
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		charIndex = currentLine->Move(frontCharIndex);
	}
}