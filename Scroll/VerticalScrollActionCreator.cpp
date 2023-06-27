//VerticalScrollActionCreator.cpp
/*
* 파일명칭:VerticalScrollActionCreator.cpp
* 기능:세로스크롤 액션의 함수를 만든다.
* 작성자:허지욱
* 작성일자:20220928
*/
#include "VerticalScrollActionCreator.h"
#include "Notepannel.h"
#include "VerticalScrollAction.h"
//생성할 클래스
#include "VerticalThumbTrack.h"
#include "VerticalThumbPosition.h"
#include "VerticalBottom.h"
#include "VerticalTop.h"
#include "VerticalLineDown.h"
#include "VerticalLineUp.h"

#include "VerticalPageDown.h"
#include "VerticalPageUp.h"


/*
* 함수명칭:VerticalScrollActionCreator
* 기능:생성자
*/
VerticalScrollActionCreator::VerticalScrollActionCreator(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* 함수명칭:~VerticalScrollActionCreator
* 기능:소멸자
*/
VerticalScrollActionCreator::~VerticalScrollActionCreator() {
}

/*
* 함수명칭:Create
* 기능:세로스크롤 액션 함수를 만든다. 
*/
VerticalScrollAction* VerticalScrollActionCreator::Create(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	VerticalScrollAction* ret = NULL;

	if (nSBCode == SB_THUMBTRACK) {
		ret = new VerticalThumbTrack(this->notepannel);
	}
	else if (nSBCode == SB_THUMBPOSITION) {
		ret = new VerticalThumbPosition(this->notepannel);
	}
	else if (nSBCode == SB_BOTTOM) {
		ret = new VerticalBottom(this->notepannel);
	}
	else if (nSBCode == SB_TOP) {
		ret = new VerticalTop(this->notepannel);
	}
	else if (nSBCode == SB_LINEDOWN) {
		ret = new VerticalLineDown(this->notepannel);
	}
	else if (nSBCode == SB_LINEUP) {
		ret = new VerticalLineUp(this->notepannel);
	}
	else if (nSBCode == SB_PAGEDOWN) {
		ret = new VerticalPageDown(this->notepannel);
	}
	else if (nSBCode == SB_PAGEUP) {
		ret = new VerticalPageUp(this->notepannel);
	}
	else if (nSBCode == SB_ENDSCROLL) {
	}
	return ret;
}