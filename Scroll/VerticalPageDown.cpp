//VerticalPageDown.cpp
/*
* ���ϸ�Ī:VerticalPageDown.cpp
* ���:���� ��ũ���� �׼��� �� �� �Ʒ��� �̵��ϴ� �̺�Ʈ�� �����ϴ� ����
* �ۼ���:������
* �ۼ�����:20220928
*/
#include "VerticalPageDown.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Caret.h"

/*
* �Լ���Ī:VerticalPageDown
* ���:������
*/
VerticalPageDown::VerticalPageDown(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~VerticalPageDown
* ���:�Ҹ���
*/
VerticalPageDown::~VerticalPageDown() {
}

/*
* �Լ���Ī:OnVScroll
* ���:�̺�Ʈ�� �´� ��ũ�� �׼��� ���Ѵ�.
*/
void VerticalPageDown::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	int position;
	int limit;
	position = this->notepannel->GetScrollPos(SB_VERT);
	limit = this->notepannel->GetScrollLimit(SB_VERT);
	position = position + this->notepannel->clientMatrix->lineNumberInPage;
	if (position > limit) {
		position = limit;
	}
	this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, position);
	this->notepannel->SetScrollPos(SB_VERT, position);
	this->notepannel->Invalidate(TRUE);
	this->notepannel->Notify();
	this->notepannel->caret->ShowCaret();
}
