//HorizontalRight.cpp
/*
* ���ϸ�Ī:HorizontalRight.cpp
* ���:���� ��ũ���� �׼��� �������� �̵��� ���� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#include "HorizontalRight.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "Caret.h"

/*
* �Լ���Ī:HorizontalRight
* ���:������
*/
HorizontalRight::HorizontalRight(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~HorizontalRight
* ���:�Ҹ���
*/
HorizontalRight::~HorizontalRight() {
}

/*
* �Լ���Ī:OnHScroll
* ���:�̺�Ʈ�� �´� ��ũ�� �׼��� ���Ѵ�.
*/
void HorizontalRight::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	int position;
	int limit;
	position = this->notepannel->GetScrollPos(SB_HORZ);
	limit = this->notepannel->GetScrollLimit(SB_HORZ);
	position++;
	if (position > limit) {
		position = limit;
	}
	this->notepannel->clientLocation->Move(position, this->notepannel->clientLocation->lineOrder);
	this->notepannel->SetScrollPos(SB_HORZ, position);
	this->notepannel->Invalidate(TRUE);
	this->notepannel->Notify();
	this->notepannel->caret->ShowCaret();
}
