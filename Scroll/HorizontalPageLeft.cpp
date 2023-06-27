//HorizontalPageLeft.cpp
/*
* ���ϸ�Ī:HorizontalPageLeft.cpp
* ���:���� ��ũ���� �׼��� �� ������ �������� �̵��� ���� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#include "HorizontalPageLeft.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Caret.h"

/*
* �Լ���Ī:HorizontalPageLeft
* ���:������
*/
HorizontalPageLeft::HorizontalPageLeft(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~HorizontalPageLeft
* ���:�Ҹ���
*/
HorizontalPageLeft::~HorizontalPageLeft() {
}

/*
* �Լ���Ī:OnHScroll
* ���:�̺�Ʈ�� �´� ��ũ�� �׼��� ���Ѵ�.
*/
void HorizontalPageLeft::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	int position;
	position = this->notepannel->GetScrollPos(SB_HORZ);
	position = position - this->notepannel->clientMatrix->width;
	if (position < 0) {
		position = 0;
	}
	this->notepannel->clientLocation->Move(position, this->notepannel->clientLocation->lineOrder);
	this->notepannel->SetScrollPos(SB_HORZ, position);
	this->notepannel->Invalidate(TRUE);
	this->notepannel->Notify();
	this->notepannel->caret->ShowCaret();
}
