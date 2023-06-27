//CtrlLeftKey.cpp
/*
* 파일명칭:CtrlLeftKey.cpp
* 기능:컨트롤과 왼쪽 화살표를 클릭했을때의 전략
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#include "CtrlLeftKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"

#include "DummyLine.h"


/*
* 함수명칭:CtrlLeftKey
* 기능:생성자
*/
CtrlLeftKey::CtrlLeftKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~CtrlLeftKey
* 기능:소멸자
*/
CtrlLeftKey::~CtrlLeftKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void CtrlLeftKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Long charIndex = -2;
	Long lineOrder = -1;
	Long order = -2;

	Long charIndexMoved = -2;
	Glyph* clonePaper = 0;
	Glyph* previousLineMerged = 0;
	Long previousLineLength = -1;

	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);

	charIndex = currentLine->GetCurrent();
	if (charIndex > -1) {
		charIndexMoved = currentLine->PreviousWord();
		if (charIndexMoved <= -1 && lineOrder > 0 && dynamic_cast<DummyLine*>(currentLine)) {
			clonePaper = this->notepannel->paper->Clone(lineOrder - 1, -1, lineOrder, charIndex);
			clonePaper->MergeAllDummyLines();
			previousLineLength = this->notepannel->paper->GetAt(lineOrder - 1)->GetLength();
			previousLineMerged = clonePaper->GetAt(0);
			previousLineMerged->Last();
			charIndexMoved = previousLineMerged->PreviousWord();
			if (charIndexMoved < previousLineLength - 1) {
				lineOrder = this->notepannel->paper->Previous();
				currentLine = this->notepannel->paper->GetAt(lineOrder);
				currentLine->Move(charIndexMoved);
			}
			delete clonePaper;
		}
	}
	else if (charIndex <= -1 && lineOrder > 0 && !dynamic_cast<DummyLine*>(currentLine)) {
		lineOrder = this->notepannel->paper->Previous();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		currentLine->Move(currentLine->GetLength() - 1);
	}
	else if (charIndex <= -1 && lineOrder > 0 && dynamic_cast<DummyLine*>(currentLine)) {
		lineOrder = this->notepannel->paper->Previous();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		currentLine->Move(currentLine->GetLength() - 1);
		currentLine->PreviousWord();
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