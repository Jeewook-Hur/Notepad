//VerticalEndScroll.cpp
/*
* 파일명칭:VerticalEndScroll.cpp
* 기능:세로 스크롤의 액션중 맨 아래로 이동하는 이벤트를 수행하는 파일
* 작성자:허지욱
* 작성일자:20220928
*/
#include "VerticalEndScroll.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "Caret.h"

/*
* 함수명칭:VerticalEndScroll
* 기능:생성자
*/
VerticalEndScroll::VerticalEndScroll(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* 함수명칭:~VerticalEndScroll
* 기능:소멸자
*/
VerticalEndScroll::~VerticalEndScroll() {
}

/*
* 함수명칭:OnVScroll
* 기능:이벤트에 맞는 스크롤 액션을 행한다.
*/
void VerticalEndScroll::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	int position;
	int limit;
	position = this->notepannel->GetScrollPos(SB_VERT);
	limit = this->notepannel->GetScrollLimit(SB_VERT);
	position = limit;

	this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, position);
	this->notepannel->SetScrollPos(SB_VERT, position);
	this->notepannel->Invalidate(TRUE);
	this->notepannel->Notify();
	this->notepannel->caret->ShowCaret();
}
