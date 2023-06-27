//HorizontalScrollActionCreator.cpp
/*
* ���ϸ�Ī:HorizontalScrollActionCreator.cpp
* ���:���ν�ũ�� �׼��� �Լ��� �����.
* �ۼ���:������
* �ۼ�����:20220929
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
* �Լ���Ī:HorizontalScrollActionCreator
* ���:������
*/
HorizontalScrollActionCreator::HorizontalScrollActionCreator(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~HorizontalScrollActionCreator
* ���:�Ҹ���
*/
HorizontalScrollActionCreator::~HorizontalScrollActionCreator() {
}

/*
* �Լ���Ī:Create
* ���:���ν�ũ�� �׼� �Լ��� �����.
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