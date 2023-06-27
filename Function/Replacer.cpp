//Replacer.cpp
/*
* 파일명칭:Replacer.cpp
* 기능:찾기와 바꾸기 내용을 기억한다.
* 작성자:허지욱
* 작성일자:2022/12/7
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
* 함수명칭:Replacer
* 기능:생성자
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
	//바꾸기를 위한 변수
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
* 함수명칭:~Replacer
* 기능:소멸자
*/
Replacer::~Replacer() {
	delete paperToReplace;
}

/*
* 함수명칭:ReplaceCurrent
* 기능:현재 선택된 내용을 바꿀 내용으로 바꾼다. 
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


	//선택된 내용을 삭제한다. 
	command = commandCreater.Create(IDM_FORMAT_DELETE);
	if (command != NULL) {
		command->Execute();
		this->notepannel->macroCommand->Add(command, 0);
		command = NULL;
	}
	//현재 위치에 바꿀 내용을 붙인다. 
	command = commandCreater.Create(IDM_FORMAT_PASTE, this->paperToReplace);
	if (command != NULL) {
		command->Execute();
		this->notepannel->macroCommand->Add(command, 1); //매크로 플래그를 올린다. 
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


	//검색방향에 맞게 현재 위치를 조정한다. 

	if (this->notepannel->finder->searchDown == TRUE) { //찾는 방향이 아래면
		//선택한 위치의 마지막 위치로 이동한다.
		lineOrder = this->notepannel->paper->Move(endLineOrder);
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		charIndex = currentLine->Move(endCharIndex);
	}
	else { //찾는 방향이 위이면
		//선택한 위치의 앞쪽으로 이동한다. 
		lineOrder = this->notepannel->paper->Move(frontLineOrder);
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		charIndex = currentLine->Move(frontCharIndex);
	}
}