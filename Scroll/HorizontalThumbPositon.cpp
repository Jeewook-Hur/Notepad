//HorizontalThumbPositon.cpp
/*
* ���ϸ�Ī:HorizontalThumbPositon.cpp
* ���:���� ��ũ���� �׼��� ������ġ �϶��� �̺�Ʈ�� �����ϴ� ����
* �ۼ���:������
* �ۼ�����:20220929
*/
#include "HorizontalThumbPositon.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "Caret.h"

/*
* �Լ���Ī:HorizontalThumbPositon
* ���:������
*/
HorizontalThumbPositon::HorizontalThumbPositon(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~HorizontalThumbPositon
* ���:�Ҹ���
*/
HorizontalThumbPositon::~HorizontalThumbPositon() {
}

/*
* �Լ���Ī:OnHScroll
* ���:�̺�Ʈ�� �´� ��ũ�� �׼��� ���Ѵ�.
*/
void HorizontalThumbPositon::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	if (nPos != this->notepannel->clientLocation->x) {//�ǽð� ��ũ���� ������ġ�� Ŭ���̾�Ʈ�� ������ġ�� ��ġ���� ������
		this->notepannel->clientLocation->Move(nPos, this->notepannel->clientLocation->lineOrder);
		this->notepannel->SetScrollPos(SB_HORZ, nPos);
		this->notepannel->Notify();
		this->notepannel->Invalidate(TRUE);
		this->notepannel->caret->ShowCaret();
	}
}
