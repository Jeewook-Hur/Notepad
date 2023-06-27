//VerticalScrollActionCreator.cpp
/*
* ���ϸ�Ī:VerticalScrollActionCreator.cpp
* ���:���ν�ũ�� �׼��� �Լ��� �����.
* �ۼ���:������
* �ۼ�����:20220928
*/
#include "VerticalScrollActionCreator.h"
#include "Notepannel.h"
#include "VerticalScrollAction.h"
//������ Ŭ����
#include "VerticalThumbTrack.h"
#include "VerticalThumbPosition.h"
#include "VerticalBottom.h"
#include "VerticalTop.h"
#include "VerticalLineDown.h"
#include "VerticalLineUp.h"

#include "VerticalPageDown.h"
#include "VerticalPageUp.h"


/*
* �Լ���Ī:VerticalScrollActionCreator
* ���:������
*/
VerticalScrollActionCreator::VerticalScrollActionCreator(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~VerticalScrollActionCreator
* ���:�Ҹ���
*/
VerticalScrollActionCreator::~VerticalScrollActionCreator() {
}

/*
* �Լ���Ī:Create
* ���:���ν�ũ�� �׼� �Լ��� �����. 
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