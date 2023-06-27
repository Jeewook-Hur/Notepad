//HorizontalLeft.cpp
/*
* 파일명칭:HorizontalLeft.cpp
* 기능:가로 스크롤의 액션중 왼쪽으로 이동할 때의 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220929
*/
#include "HorizontalLeft.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "Caret.h"

/*
* 함수명칭:HorizontalLeft
* 기능:생성자
*/
HorizontalLeft::HorizontalLeft(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* 함수명칭:~HorizontalLeft
* 기능:소멸자
*/
HorizontalLeft::~HorizontalLeft() {
}

/*
* 함수명칭:OnHScroll
* 기능:이벤트에 맞는 스크롤 액션을 행한다.
*/
void HorizontalLeft::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	int position;
	position = this->notepannel->GetScrollPos(SB_HORZ);
	position--;
	if (position < 0) {
		position = 0;
	}
	this->notepannel->clientLocation->Move(position, this->notepannel->clientLocation->lineOrder);
	this->notepannel->SetScrollPos(SB_HORZ, position);
	this->notepannel->Invalidate(TRUE);
	this->notepannel->Notify();
	this->notepannel->caret->ShowCaret();
}
