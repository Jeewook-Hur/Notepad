//HorizontalThumbTrack.cpp
/*
* ���ϸ�Ī:HorizontalThumbTrack.cpp
* ���:���� ��ũ���� �׼��� ������ �̺�Ʈ�� �����ϴ� ����
* �ۼ���:������
* �ۼ�����:20220929
*/
#include "HorizontalThumbTrack.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "Caret.h"

/*
* �Լ���Ī:HorizontalThumbTrack
* ���:������
*/
HorizontalThumbTrack::HorizontalThumbTrack(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~HorizontalThumbTrack
* ���:�Ҹ���
*/
HorizontalThumbTrack::~HorizontalThumbTrack() {
}

/*
* �Լ���Ī:OnHScroll
* ���:�̺�Ʈ�� �´� ��ũ�� �׼��� ���Ѵ�.
*/
void HorizontalThumbTrack::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	if (nPos != this->notepannel->clientLocation->x) {//�ǽð� ��ũ���� ������ġ�� Ŭ���̾�Ʈ�� ������ġ�� ��ġ���� ������
		this->notepannel->clientLocation->Move(nPos, this->notepannel->clientLocation->lineOrder);
		this->notepannel->SetScrollPos(SB_HORZ, nPos);
		this->notepannel->Notify();
		this->notepannel->Invalidate(TRUE);
		this->notepannel->caret->ShowCaret();
	}
}
