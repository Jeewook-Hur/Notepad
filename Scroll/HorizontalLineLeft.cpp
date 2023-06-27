//HorizontalLineLeft.cpp
/*
* 파일명칭:HorizontalLineLeft.cpp
* 기능:가로 스크롤의 액션중 왼쪽으로 한 줄이동할 때의 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220928
*/
#include "HorizontalLineLeft.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "ClientLocation.h"
#include "Caret.h"

/*
* 함수명칭:HorizontalLineLeft
* 기능:생성자
*/
HorizontalLineLeft::HorizontalLineLeft(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* 함수명칭:~HorizontalLineLeft
* 기능:소멸자
*/
HorizontalLineLeft::~HorizontalLineLeft() {
}

/*
* 함수명칭:OnHScroll
* 기능:이벤트에 맞는 스크롤 액션을 행한다.
*/
void HorizontalLineLeft::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	int position;
	int charWidth;
	position = this->notepannel->GetScrollPos(SB_HORZ);
	charWidth = this->notepannel->characterMatrix->widths[65];
	position = position - charWidth;
	if (position < 0) {
		position = 0;
	}
	this->notepannel->clientLocation->Move(position, this->notepannel->clientLocation->lineOrder);
	this->notepannel->SetScrollPos(SB_HORZ, position);
	this->notepannel->Invalidate(TRUE);
	this->notepannel->Notify();
	this->notepannel->caret->ShowCaret();
}
