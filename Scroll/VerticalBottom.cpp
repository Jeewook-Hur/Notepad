//VerticalBottom.cpp
/*
* ���ϸ�Ī:VerticalBottom.cpp
* ���:���� ��ũ���� �׼��� �Ʒ��� �̵��ϴ� �̺�Ʈ�� �����ϴ� ����
* �ۼ���:������
* �ۼ�����:20220928
*/
#include "VerticalBottom.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "Caret.h"

/*
* �Լ���Ī:VerticalBottom
* ���:������
*/
VerticalBottom::VerticalBottom(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~VerticalBottom
* ���:�Ҹ���
*/
VerticalBottom::~VerticalBottom() {
}

/*
* �Լ���Ī:OnVScroll
* ���:�̺�Ʈ�� �´� ��ũ�� �׼��� ���Ѵ�.
*/
void VerticalBottom::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	int position;
	int limit;
	int previous;
	position = this->notepannel->GetScrollPos(SB_VERT);
	limit = this->notepannel->GetScrollLimit(SB_VERT);
	previous = position;
	position++;
	if (position > limit) {
		position = limit;
	}
	if (position != previous) {
		this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, position);
		this->notepannel->SetScrollPos(SB_VERT, position);
		this->notepannel->Invalidate(TRUE);
		this->notepannel->Notify();
	}
	this->notepannel->caret->ShowCaret();
}
