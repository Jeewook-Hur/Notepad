//Finder.cpp
/*
* 파일명칭:Finder.cpp
* 기능:찾기와 바꾸기 내용을 기억한다.
* 작성자:허지욱
* 작성일자:2022/12/7
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
* 함수명칭:Finder
* 기능:생성자
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
	this->findNext = cFindReplaceDialog->FindNext(); //찾기창에서 다음 찾기를 클릭했는지 확인한다.
	this->isTerminating = cFindReplaceDialog->IsTerminating(); //찾기창에서 닫기를 클릭했는지 확인한다.
	this->searchDown = cFindReplaceDialog->SearchDown(); //찾는 방향을 읽는다.
	this->matchWholeWord = cFindReplaceDialog->MatchWholeWord(); //단어단위로 찾기가 체크되었는지 확인한다. 
	this->matchCase = cFindReplaceDialog->MatchCase(); //대소문자 구분 여부가 체크되었는지 확인한다.
	this->find = (LPCSTR)(cFindReplaceDialog->GetFindString()); //찾을 내용을 읽는다.

	
}

/*
* 함수명칭:~Finder
* 기능:소멸자
*/
Finder::~Finder() {
}

/*
* 함수명칭:Find
* 기능:찾는 내용을 메모장에서 찾는다. 
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

	//검색어로 검색결과를 초기화한다.
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

	//할당해제
	//delete[] this->notepannel->resultFound->lineOrders;
	//delete[] this->notepannel->resultFound->charIndexes;

	if (paperToFindNumber > 0 && matchCase == TRUE && matchWholeWord == FALSE) { //대소문자 구분이 되어있으면 종이에서 치환한 종이를 대소문자 구분해서 찾는다.
		this->notepannel->paper->FindPaper(paperToFind, &this->notepannel->resultFound->lineOrders, &this->notepannel->resultFound->charIndexes, &this->notepannel->resultFound->count);
	}
	else if (paperToFindNumber > 0 && matchCase == FALSE && matchWholeWord == FALSE) { //대소문자 구분이 안되어있으면 종이에서 치환한 종이를 찾는다.
		this->notepannel->paper->FindPaperUpperLower(paperToFind, &this->notepannel->resultFound->lineOrders, &this->notepannel->resultFound->charIndexes, &this->notepannel->resultFound->count);
	}
	else if (paperToFindNumber > 0 && matchCase == TRUE && matchWholeWord == TRUE) { //대소문자 구분이 되어있으면 종이에서 치환한 종이를 대소문자 구분해서 찾는다.
		clonePaper->FindPaper(paperToFindMatch, &this->notepannel->resultFound->lineOrders, &this->notepannel->resultFound->charIndexes, &this->notepannel->resultFound->count);
	}
	else if (paperToFindNumber > 0 && matchCase == FALSE && matchWholeWord == TRUE) { //대소문자 구분이 안되어있으면 종이에서 치환한 종이를 찾는다.
		clonePaper->FindPaperUpperLower(paperToFindMatch, &this->notepannel->resultFound->lineOrders, &this->notepannel->resultFound->charIndexes, &this->notepannel->resultFound->count);
	}

	//할당해제
	delete blank;
	delete clonePaper;
	delete paperToFindMatch;

	return this->notepannel->resultFound->count; //찾은 개수를 반환한다. 
}

/*
* 함수명칭:SearchNear
* 기능:검색결과에서 입력받은 위치 근처를 찾는다. 
*/
Long Finder::SearchNear(Long lineOrder, Long charIndex) {
	Long count = this->notepannel->resultFound->count;
	Long(*lineOrders) = this->notepannel->resultFound->lineOrders;
	Long(*charIndexes) = this->notepannel->resultFound->charIndexes;
	Long ret = -10;
	Long i = 0;
	UINT lineWrapState = -1;
	lineWrapState = this->notepannel->notepad->cMenu.GetMenuState(IDM_FORMAT_LINEWRAP, MF_BYCOMMAND);


	//현재 위치로부터 다음 위치를 찾는다.
	while (i < count && lineOrders[i] < lineOrder) { //검색 위치의 줄이 입력받은 위치의 줄보다 작은동안 반복한다. 
		i++;
	}
	while (i < count && lineOrders[i] == lineOrder && charIndexes[i] < charIndex) {
		i++;
	}
	if (searchDown == FALSE) { //찾는 방향이 위 이고 단어단위로 찾기가 아니면 
		//이전 위치로 이동한다. 
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
* 함수명칭:SelectResult
* 기능:검색 결과를 선택한다. 
*/
void Finder::SelectResult(Long index) {
	Glyph* currentLine = 0;
	Glyph* paperToFind = this->notepannel->resultFound->paperToFind;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long otherPaperLength = -1;
	Long otherPaperLastLineLength = -1;
	//선택을 위한 영역
	Long frontLineOrder;
	Long frontCharIndex;
	Long endLineOrder;
	Long endCharIndex;

	Long(*lineOrders) = this->notepannel->resultFound->lineOrders;
	Long(*charIndexes) = this->notepannel->resultFound->charIndexes;

	//찾는 종이의 길이와 마지막 줄의 길이를 확인한다.
	otherPaperLength = paperToFind->GetLength();
	lineOrder = paperToFind->Last();
	currentLine = paperToFind->GetAt(lineOrder);
	otherPaperLastLineLength = currentLine->GetLength();
	//위치부터 찾는 문자의 길이만큼 선택한다.
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


	if (searchDown == TRUE) { //찾는 방향이 아래면
		//선택한 위치의 마지막 위치로 이동한다.
		lineOrder = this->notepannel->paper->Move(endLineOrder);
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		currentLine->Move(endCharIndex);
	}
	else { //찾는 방향이 위이면
		//선택한 위치의 앞쪽으로 이동한다. 
		lineOrder = this->notepannel->paper->Move(frontLineOrder);
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		currentLine->Move(frontCharIndex);
	}
}