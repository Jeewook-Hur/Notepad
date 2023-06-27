//VerticalLineUp.cpp
/*
* ���ϸ�Ī:VerticalLineUp.cpp
* ���:���� ��ũ���� �׼��� ���� �̵��ϴ� �̺�Ʈ�� �����ϴ� ����
* �ۼ���:������
* �ۼ�����:20220928
*/
#include "VerticalLineUp.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "Caret.h"

/*
* �Լ���Ī:VerticalLineUp
* ���:������
*/
VerticalLineUp::VerticalLineUp(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~VerticalLineUp
* ���:�Ҹ���
*/
VerticalLineUp::~VerticalLineUp() {
}

/*
* �Լ���Ī:OnVScroll
* ���:�̺�Ʈ�� �´� ��ũ�� �׼��� ���Ѵ�.
*/
void VerticalLineUp::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	int position;
	int previous;
	position = this->notepannel->GetScrollPos(SB_VERT);
	previous = position;
	position--;
	if (position < 0) {
		position = 0;
	}
	if (position != previous) {
		this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, position);
		this->notepannel->SetScrollPos(SB_VERT, position);
		this->notepannel->Invalidate(TRUE);
		this->notepannel->Notify();
	}
	this->notepannel->caret->ShowCaret();
}
