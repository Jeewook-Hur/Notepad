//Finder.cpp
/*
* ���ϸ�Ī:Finder.cpp
* ���:ã��� �ٲٱ� ������ ����Ѵ�.
* �ۼ���:������
* �ۼ�����:2022/12/7
*/
#include "Finder.h"
#include "Notepannel.h"
#include "Notepad.h"

#include "Select.h"
#include "Caret.h"
#include "ResultFound.h"

#include "GlyphCreater.h"
#include "Paper.h"
#include "resource.h"
#include <afxdlgs.h>

/*
* �Լ���Ī:Finder
* ���:������
*/
Finder::Finder(Notepannel* notepannel, string find, string replace)
	:notepannel(notepannel), find(find) {
	this->findNext = 1;
	this->isTerminating = 0;
	this->searchDown = 1;
	this->matchWholeWord = 0;
	this->matchCase = 0;
	
	
	
}
Finder::Finder(Notepannel* notepannel, WPARAM wParam, LPARAM lParam) : notepannel(notepannel) {
	CFindReplaceDialog* cFindReplaceDialog = CFindReplaceDialog::GetNotifier(lParam);
	this->findNext = cFindReplaceDialog->FindNext(); //ã��â���� ���� ã�⸦ Ŭ���ߴ��� Ȯ���Ѵ�.
	this->isTerminating = cFindReplaceDialog->IsTerminating(); //ã��â���� �ݱ⸦ Ŭ���ߴ��� Ȯ���Ѵ�.
	this->searchDown = cFindReplaceDialog->SearchDown(); //ã�� ������ �д´�.
	this->matchWholeWord = cFindReplaceDialog->MatchWholeWord(); //�ܾ������ ã�Ⱑ üũ�Ǿ����� Ȯ���Ѵ�. 
	this->matchCase = cFindReplaceDialog->MatchCase(); //��ҹ��� ���� ���ΰ� üũ�Ǿ����� Ȯ���Ѵ�.
	this->find = (LPCSTR)(cFindReplaceDialog->GetFindString()); //ã�� ������ �д´�.

	
}

/*
* �Լ���Ī:~Finder
* ���:�Ҹ���
*/
Finder::~Finder() {
}

/*
* �Լ���Ī:Find
* ���:ã�� ������ �޸��忡�� ã�´�. 
*/
Long Finder::Find() {
	GlyphCreater glyphCreater;
	Glyph* currentLine = 0;
	Glyph* paperToFind = 0;


	//MatchPaper
	Glyph* paperToFindMatch = 0;
	Glyph* clonePaper = 0;
	Glyph* blank = glyphCreater.Create(" ");

	Long paperToFindNumber;
	Long i = 0;

	//�˻���� �˻������ �ʱ�ȭ�Ѵ�.
	delete this->notepannel->resultFound;
	this->notepannel->resultFound = new ResultFound(this->find);

	paperToFind = this->notepannel->resultFound->paperToFind;

	if (this->matchWholeWord == TRUE) {
		//MatchPaper
		clonePaper = this->notepannel->paper->Clone();
		paperToFindMatch = this->notepannel->resultFound->paperToFind->Clone();
		i = 0;
		while (i < clonePaper->GetLength()) {
			currentLine = clonePaper->GetAt(i);
			currentLine->Add(0, blank->Clone());
			currentLine->Add(currentLine->GetLength(), blank->Clone());
			i++;
		}
		i = 0;
		while (i < paperToFindMatch->GetLength()) {
			currentLine = paperToFindMatch->GetAt(i);
			currentLine->Add(0, blank->Clone());
			currentLine->Add(currentLine->GetLength(), blank->Clone());
			i++;
		}
	}

	paperToFindNumber = this->notepannel->resultFound->paperToFind->GetCharNumber();

	//�Ҵ�����
	//delete[] this->notepannel->resultFound->lineOrders;
	//delete[] this->notepannel->resultFound->charIndexes;

	if (paperToFindNumber > 0 && matchCase == TRUE && matchWholeWord == FALSE) { //��ҹ��� ������ �Ǿ������� ���̿��� ġȯ�� ���̸� ��ҹ��� �����ؼ� ã�´�.
		this->notepannel->paper->FindPaper(paperToFind, &this->notepannel->resultFound->lineOrders, &this->notepannel->resultFound->charIndexes, &this->notepannel->resultFound->count);
	}
	else if (paperToFindNumber > 0 && matchCase == FALSE && matchWholeWord == FALSE) { //��ҹ��� ������ �ȵǾ������� ���̿��� ġȯ�� ���̸� ã�´�.
		this->notepannel->paper->FindPaperUpperLower(paperToFind, &this->notepannel->resultFound->lineOrders, &this->notepannel->resultFound->charIndexes, &this->notepannel->resultFound->count);
	}
	else if (paperToFindNumber > 0 && matchCase == TRUE && matchWholeWord == TRUE) { //��ҹ��� ������ �Ǿ������� ���̿��� ġȯ�� ���̸� ��ҹ��� �����ؼ� ã�´�.
		clonePaper->FindPaper(paperToFindMatch, &this->notepannel->resultFound->lineOrders, &this->notepannel->resultFound->charIndexes, &this->notepannel->resultFound->count);
	}
	else if (paperToFindNumber > 0 && matchCase == FALSE && matchWholeWord == TRUE) { //��ҹ��� ������ �ȵǾ������� ���̿��� ġȯ�� ���̸� ã�´�.
		clonePaper->FindPaperUpperLower(paperToFindMatch, &this->notepannel->resultFound->lineOrders, &this->notepannel->resultFound->charIndexes, &this->notepannel->resultFound->count);
	}

	//�Ҵ�����
	delete blank;
	delete clonePaper;
	delete paperToFindMatch;

	return this->notepannel->resultFound->count; //ã�� ������ ��ȯ�Ѵ�. 
}

/*
* �Լ���Ī:SearchNear
* ���:�˻�������� �Է¹��� ��ġ ��ó�� ã�´�. 
*/
Long Finder::SearchNear(Long lineOrder, Long charIndex) {
	Long count = this->notepannel->resultFound->count;
	Long(*lineOrders) = this->notepannel->resultFound->lineOrders;
	Long(*charIndexes) = this->notepannel->resultFound->charIndexes;
	Long ret = -10;
	Long i = 0;
	UINT lineWrapState = -1;
	lineWrapState = this->notepannel->notepad->cMenu.GetMenuState(IDM_FORMAT_LINEWRAP, MF_BYCOMMAND);


	//���� ��ġ�κ��� ���� ��ġ�� ã�´�.
	while (i < count && lineOrders[i] < lineOrder) { //�˻� ��ġ�� ���� �Է¹��� ��ġ�� �ٺ��� �������� �ݺ��Ѵ�. 
		i++;
	}
	while (i < count && lineOrders[i] == lineOrder && charIndexes[i] < charIndex) {
		i++;
	}
	if (searchDown == FALSE) { //ã�� ������ �� �̰� �ܾ������ ã�Ⱑ �ƴϸ� 
		//���� ��ġ�� �̵��Ѵ�. 
		i--;
		if (lineWrapState == MF_CHECKED && matchWholeWord == FALSE) {
			i--;
		}

	}
	if (i < count && i >= 0) {
		ret = i;
	}

	return ret;
}

/*
* �Լ���Ī:SelectResult
* ���:�˻� ����� �����Ѵ�. 
*/
void Finder::SelectResult(Long index) {
	Glyph* currentLine = 0;
	Glyph* paperToFind = this->notepannel->resultFound->paperToFind;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long otherPaperLength = -1;
	Long otherPaperLastLineLength = -1;
	//������ ���� ����
	Long frontLineOrder;
	Long frontCharIndex;
	Long endLineOrder;
	Long endCharIndex;

	Long(*lineOrders) = this->notepannel->resultFound->lineOrders;
	Long(*charIndexes) = this->notepannel->resultFound->charIndexes;

	//ã�� ������ ���̿� ������ ���� ���̸� Ȯ���Ѵ�.
	otherPaperLength = paperToFind->GetLength();
	lineOrder = paperToFind->Last();
	currentLine = paperToFind->GetAt(lineOrder);
	otherPaperLastLineLength = currentLine->GetLength();
	//��ġ���� ã�� ������ ���̸�ŭ �����Ѵ�.
	frontLineOrder = lineOrders[index];
	frontCharIndex = charIndexes[index];
	if (otherPaperLength <= 1) {
		endLineOrder = frontLineOrder;
		endCharIndex = frontCharIndex + otherPaperLastLineLength;
	}
	else {
		endLineOrder = frontLineOrder + otherPaperLength - 1;
		endCharIndex = otherPaperLastLineLength - 1;
	}
	delete this->notepannel->select;
	this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);


	if (searchDown == TRUE) { //ã�� ������ �Ʒ���
		//������ ��ġ�� ������ ��ġ�� �̵��Ѵ�.
		lineOrder = this->notepannel->paper->Move(endLineOrder);
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		currentLine->Move(endCharIndex);
	}
	else { //ã�� ������ ���̸�
		//������ ��ġ�� �������� �̵��Ѵ�. 
		lineOrder = this->notepannel->paper->Move(frontLineOrder);
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		currentLine->Move(frontCharIndex);
	}
}