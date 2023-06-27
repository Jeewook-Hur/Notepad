//HorizontalLineLeft.cpp
/*
* ���ϸ�Ī:HorizontalLineLeft.cpp
* ���:���� ��ũ���� �׼��� �������� �� ���̵��� ���� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220928
*/
#include "HorizontalLineLeft.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "ClientLocation.h"
#include "Caret.h"

/*
* �Լ���Ī:HorizontalLineLeft
* ���:������
*/
HorizontalLineLeft::HorizontalLineLeft(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~HorizontalLineLeft
* ���:�Ҹ���
*/
HorizontalLineLeft::~HorizontalLineLeft() {
}

/*
* �Լ���Ī:OnHScroll
* ���:�̺�Ʈ�� �´� ��ũ�� �׼��� ���Ѵ�.
*/
void HorizontalLineLeft::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	int position;
	int charWidth;
	position = this->notepannel->GetScrollPos(SB_HORZ);
	charWidth = this->notepannel->characterMatrix->widths[65];
	position = position - charWidth;
	if (position < 0) {
		position = 0;
	}
	this->notepannel->clientLocation->Move(position, this->notepannel->clientLocation->lineOrder);
	this->notepannel->SetScrollPos(SB_HORZ, position);
	this->notepannel->Invalidate(TRUE);
	this->notepannel->Notify();
	this->notepannel->caret->ShowCaret();
}
