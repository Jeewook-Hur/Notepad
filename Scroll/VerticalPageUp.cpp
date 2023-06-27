//VerticalPageUp.cpp
/*
* 파일명칭:VerticalPageUp.cpp
* 기능:세로 스크롤의 액션중 한 페이지 위로 이동하는 이벤트를 수행하는 파일
* 작성자:허지욱
* 작성일자:20220928
*/
#include "VerticalPageUp.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Caret.h"

/*
* 함수명칭:VerticalPageUp
* 기능:생성자
*/
VerticalPageUp::VerticalPageUp(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* 함수명칭:~VerticalPageUp
* 기능:소멸자
*/
VerticalPageUp::~VerticalPageUp() {
}

/*
* 함수명칭:OnVScroll
* 기능:이벤트에 맞는 스크롤 액션을 행한다.
*/
void VerticalPageUp::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	int position;
	position = this->notepannel->GetScrollPos(SB_VERT);
	position = position - this->notepannel->clientMatrix->lineNumberInPage;
	if (position < 0) {
		position = 0;
	}
	this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, position);
	this->notepannel->SetScrollPos(SB_VERT, position);
	this->notepannel->Invalidate(TRUE);
	this->notepannel->Notify();
	this->notepannel->caret->ShowCaret();
}
