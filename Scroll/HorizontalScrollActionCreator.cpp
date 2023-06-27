//HorizontalScrollActionCreator.cpp
/*
* 파일명칭:HorizontalScrollActionCreator.cpp
* 기능:가로스크롤 액션의 함수를 만든다.
* 작성자:허지욱
* 작성일자:20220929
*/
#include "HorizontalScrollActionCreator.h"
#include "Notepannel.h"
#include "HorizontalScrollAction.h"

#include "HorizontalThumbTrack.h"
#include "HorizontalThumbPositon.h"
#include "HorizontalLeft.h"
#include "HorizontalRight.h"
#include "HorizontalLineLeft.h"
#include "HorizontalLineRight.h"
#include "HorizontalPageLeft.h"
#include "HorizontalPageRight.h"


/*
* 함수명칭:HorizontalScrollActionCreator
* 기능:생성자
*/
HorizontalScrollActionCreator::HorizontalScrollActionCreator(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* 함수명칭:~HorizontalScrollActionCreator
* 기능:소멸자
*/
HorizontalScrollActionCreator::~HorizontalScrollActionCreator() {
}

/*
* 함수명칭:Create
* 기능:가로스크롤 액션 함수를 만든다.
*/
HorizontalScrollAction* HorizontalScrollActionCreator::Create(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	HorizontalScrollAction* ret = NULL;

	if (nSBCode == SB_THUMBTRACK) {
		ret = new HorizontalThumbTrack(this->notepannel);
	}
	else if (nSBCode == SB_THUMBPOSITION) {
		ret = new HorizontalThumbPositon(this->notepannel);
	}
	else if (nSBCode == SB_LEFT) {
		ret = new HorizontalLeft(this->notepannel);
	}
	else if (nSBCode == SB_RIGHT) {
		ret = new HorizontalRight(this->notepannel);
	}
	else if (nSBCode == SB_LINELEFT) {
		ret = new HorizontalLineLeft(this->notepannel);
	}
	else if (nSBCode == SB_LINERIGHT) {
		ret = new HorizontalLineRight(this->notepannel);
	}
	else if (nSBCode == SB_PAGELEFT) {
		ret = new HorizontalPageLeft(this->notepannel);
	}
	else if (nSBCode == SB_PAGERIGHT) {
		ret = new HorizontalPageRight(this->notepannel);
	}
	else if (nSBCode == SB_ENDSCROLL) {
	}
	return ret;
}