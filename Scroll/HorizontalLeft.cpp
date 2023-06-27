//HorizontalLeft.cpp
/*
* ���ϸ�Ī:HorizontalLeft.cpp
* ���:���� ��ũ���� �׼��� �������� �̵��� ���� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#include "HorizontalLeft.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "Caret.h"

/*
* �Լ���Ī:HorizontalLeft
* ���:������
*/
HorizontalLeft::HorizontalLeft(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~HorizontalLeft
* ���:�Ҹ���
*/
HorizontalLeft::~HorizontalLeft() {
}

/*
* �Լ���Ī:OnHScroll
* ���:�̺�Ʈ�� �´� ��ũ�� �׼��� ���Ѵ�.
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
