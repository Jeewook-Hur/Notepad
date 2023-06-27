//VerticalThumbPosition.cpp
/*
* ���ϸ�Ī:VerticalThumbPosition.cpp
* ���:���� ��ũ���� �׼��� ������ �̺�Ʈ�� �����ϴ� ����
* �ۼ���:������
* �ۼ�����:20220928
*/
#include "VerticalThumbPosition.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "Caret.h"

/*
* �Լ���Ī:VerticalThumbPosition
* ���:������
*/
VerticalThumbPosition::VerticalThumbPosition(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~VerticalThumbPosition
* ���:�Ҹ���
*/
VerticalThumbPosition::~VerticalThumbPosition() {
}

/*
* �Լ���Ī:OnVScroll
* ���:�̺�Ʈ�� �´� ��ũ�� �׼��� ���Ѵ�.
*/
void VerticalThumbPosition::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	if (nPos != this->notepannel->clientLocation->lineOrder) {//�ǽð� ��ũ���� ������ġ�� Ŭ���̾�Ʈ�� ������ġ�� ��ġ���� ������
		this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, nPos);
		this->notepannel->SetScrollPos(SB_VERT, nPos);
		this->notepannel->Notify();
		this->notepannel->Invalidate(TRUE);
		this->notepannel->caret->ShowCaret();
	}
}
