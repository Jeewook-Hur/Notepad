//CtrlRightKey.cpp
/*
* 파일명칭:CtrlRightKey.cpp
* 기능:컨트롤과 오른쪽 화살표를 클릭했을때의 전략
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#include "CtrlRightKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"
#include "DummyLine.h"

/*
* 함수명칭:CtrlRightKey
* 기능:생성자
*/
CtrlRightKey::CtrlRightKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~CtrlRightKey
* 기능:소멸자
*/
CtrlRightKey::~CtrlRightKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void CtrlRightKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Long charIndex = -2;
	Long lineOrder = -1;
	Long order = -2;

	Glyph* nextLine = 0;
	Long nextLineLastIndex = -1;

	Long charIndexMoved = -2;
	Glyph* clonePaper = 0;
	Glyph* lineMerged = 0;
	Long currentLineLastIndex = -1;

	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	
	if (lineOrder < this->notepannel->paper->GetLength() - 1) {
		nextLine = this->notepannel->paper->GetAt(lineOrder + 1);
		nextLineLastIndex = nextLine->Last();
	}

	if (charIndex < currentLine->GetLength() - 1) {
		charIndexMoved = currentLine->NextWord();

		if (charIndexMoved >= currentLine->GetLength() - 1 && lineOrder < this->notepannel->paper->GetLength() - 1 && dynamic_cast<DummyLine*>(nextLine)) {
			currentLineLastIndex = currentLine->GetLength() - 1;
			clonePaper = this->notepannel->paper->Clone(lineOrder, -1, lineOrder + 1, nextLineLastIndex);
			clonePaper->MergeAllDummyLines();
			lineMerged = clonePaper->GetAt(0);
			lineMerged->Move(currentLineLastIndex);
			lineMerged->PreviousWord();
			charIndexMoved = lineMerged->NextWord();
			if (charIndexMoved > currentLineLastIndex) {
				lineOrder = this->notepannel->paper->Next();
				currentLine = this->notepannel->paper->GetAt(lineOrder);
				currentLine->First();
				currentLine->NextWord();
			}
			delete clonePaper;
		}
	}
	else if (charIndex >= currentLine->GetLength() - 1 && lineOrder < this->notepannel->paper->GetLength() - 1 && !dynamic_cast<DummyLine*>(nextLine)) {
		lineOrder = this->notepannel->paper->Next();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		currentLine->Move(-1);
	}
	else if (charIndex >= currentLine->GetLength() - 1 && lineOrder < this->notepannel->paper->GetLength() - 1 && dynamic_cast<DummyLine*>(nextLine)) {
		lineOrder = this->notepannel->paper->Next();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		currentLine->Move(-1);
		currentLine->NextWord();
	}
	//현재 위치를 구한다. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//현재 위치로 선택 클래스를 초기화한다. 
	delete this->notepannel->select;
	this->notepannel->select = new Select(this->notepannel, charIndex, lineOrder, charIndex, lineOrder);
	//업데이트 갱신 함수를 호출한다.
	//캐럿을 업데이트 한다. 
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//클라이언트 갱신 함수를 호출한다.
	this->notepannel->Invalidate(TRUE);
	//캐럿을 보이게한다.
	this->notepannel->caret->ShowCaret();
}