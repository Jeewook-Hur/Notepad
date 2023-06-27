//LeftKey.cpp
/*
* 파일명칭:LeftKey.cpp
* 기능:왼쪽 화살표를 클릭했을때의 전략
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#include "LeftKey.h"
#include "Notepannel.h"
#include "Caret.h"
#include "CharacterMatrix.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"

#include "DummyLine.h"

/*
* 함수명칭:LeftKey
* 기능:생성자
*/
LeftKey::LeftKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~LeftKey
* 기능:소멸자
*/
LeftKey::~LeftKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void LeftKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Long charIndex = -2;
	Long lineOrder = -1;
	Long order = -2;


	if (this->notepannel->isSelected == FALSE) {//선택되었다는 표시가 내려가 있으면
		lineOrder = this->notepannel->paper->GetCurrent();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		charIndex = currentLine->GetCurrent();
		if (charIndex > -1) {
			currentLine->Previous();
		}
		else if (charIndex <= -1 && lineOrder > 0 && !dynamic_cast<DummyLine*>(currentLine)) {
			lineOrder = this->notepannel->paper->Previous();
			currentLine = this->notepannel->paper->GetAt(lineOrder);
			currentLine->Move(currentLine->GetLength() - 1);
		}
		else if (charIndex <= -1 && lineOrder > 0 && dynamic_cast<DummyLine*>(currentLine)) {
			lineOrder = this->notepannel->paper->Previous();
			currentLine = this->notepannel->paper->GetAt(lineOrder);
			currentLine->Move(currentLine->GetLength() - 2);
		}

		//업데이트 갱신 함수를 호출한다.
		this->notepannel->clientMoveCheck = TRUE;
		this->notepannel->Notify();
	}
	else { //선택되었다는 표시가 올라가 있으면
		//선택되었다는 플래그를 내린다.
		this->notepannel->isSelected = FALSE;
		//현재위치를 선택하기의 앞 위치로 갱신한다.
		lineOrder = this->notepannel->paper->Move(this->notepannel->select->frontLineOrder);
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		charIndex = currentLine->Move(this->notepannel->select->frontXIndex);
		//업데이트 갱신 함수를 호출한다.
		this->notepannel->clientMoveCheck = TRUE;
		this->notepannel->Notify();
		//클라이언트 갱신 함수를 호출한다.
		this->notepannel->Invalidate(TRUE);
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