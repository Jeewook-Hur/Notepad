//HorizontalThumbTrack.cpp
/*
* 파일명칭:HorizontalThumbTrack.cpp
* 기능:가로 스크롤의 액션중 끌때의 이벤트를 수행하는 파일
* 작성자:허지욱
* 작성일자:20220929
*/
#include "HorizontalThumbTrack.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "Caret.h"

/*
* 함수명칭:HorizontalThumbTrack
* 기능:생성자
*/
HorizontalThumbTrack::HorizontalThumbTrack(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* 함수명칭:~HorizontalThumbTrack
* 기능:소멸자
*/
HorizontalThumbTrack::~HorizontalThumbTrack() {
}

/*
* 함수명칭:OnHScroll
* 기능:이벤트에 맞는 스크롤 액션을 행한다.
*/
void HorizontalThumbTrack::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	if (nPos != this->notepannel->clientLocation->x) {//실시간 스크롤의 현재위치가 클라이언트의 현재위치와 일치하지 않으면
		this->notepannel->clientLocation->Move(nPos, this->notepannel->clientLocation->lineOrder);
		this->notepannel->SetScrollPos(SB_HORZ, nPos);
		this->notepannel->Notify();
		this->notepannel->Invalidate(TRUE);
		this->notepannel->caret->ShowCaret();
	}
}
