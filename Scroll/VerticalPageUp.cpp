//VerticalPageUp.cpp
/*
* ���ϸ�Ī:VerticalPageUp.cpp
* ���:���� ��ũ���� �׼��� �� ������ ���� �̵��ϴ� �̺�Ʈ�� �����ϴ� ����
* �ۼ���:������
* �ۼ�����:20220928
*/
#include "VerticalPageUp.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Caret.h"

/*
* �Լ���Ī:VerticalPageUp
* ���:������
*/
VerticalPageUp::VerticalPageUp(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~VerticalPageUp
* ���:�Ҹ���
*/
VerticalPageUp::~VerticalPageUp() {
}

/*
* �Լ���Ī:OnVScroll
* ���:�̺�Ʈ�� �´� ��ũ�� �׼��� ���Ѵ�.
*/
void VerticalPageUp::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	int position;
	position = this->notepannel->GetScrollPos(SB_VERT);
	position = position - this->notepannel->clientMatrix->lineNumberInPage;
	if (position < 0) {
		position = 0;
	}
	this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, position);
	this->notepannel->SetScrollPos(SB_VERT, position);
	this->notepannel->Invalidate(TRUE);
	this->notepannel->Notify();
	this->notepannel->caret->ShowCaret();
}
