//HorizontalLineRight.cpp
/*
* ���ϸ�Ī:HorizontalLineRight.cpp
* ���:���� ��ũ���� �׼��� �� �� �������� �̵��� ���� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#include "HorizontalLineRight.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "ClientLocation.h"
#include "Caret.h"

/*
* �Լ���Ī:HorizontalLineRight
* ���:������
*/
HorizontalLineRight::HorizontalLineRight(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~HorizontalLineRight
* ���:�Ҹ���
*/
HorizontalLineRight::~HorizontalLineRight() {
}

/*
* �Լ���Ī:OnHScroll
* ���:�̺�Ʈ�� �´� ��ũ�� �׼��� ���Ѵ�.
*/
void HorizontalLineRight::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	int position;
	int limit;
	int charWidth;
	position = this->notepannel->GetScrollPos(SB_HORZ);
	limit = this->notepannel->GetScrollLimit(SB_HORZ);
	charWidth = this->notepannel->characterMatrix->widths[65];
	position = position + charWidth;
	if (position > limit) {
		position = limit;
	}
	this->notepannel->clientLocation->Move(position, this->notepannel->clientLocation->lineOrder);
	this->notepannel->SetScrollPos(SB_HORZ, position);
	this->notepannel->Invalidate(TRUE);
	this->notepannel->Notify();
	this->notepannel->caret->ShowCaret();
}
