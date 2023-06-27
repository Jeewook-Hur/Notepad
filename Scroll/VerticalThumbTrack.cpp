//VerticalThumbTrack.cpp
/*
* ���ϸ�Ī:VerticalThumbTrack.cpp
* ���:���� ��ũ���� �׼��� ������ �̺�Ʈ�� �����ϴ� ����
* �ۼ���:������
* �ۼ�����:20220928
*/
#include "VerticalThumbTrack.h"
#include "Notepannel.h"
#include "ClientLocation.h"
#include "Caret.h"

/*
* �Լ���Ī:VerticalThumbTrack
* ���:������
*/
VerticalThumbTrack::VerticalThumbTrack(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~VerticalThumbTrack
* ���:�Ҹ���
*/
VerticalThumbTrack::~VerticalThumbTrack() {
}

/*
* �Լ���Ī:OnVScroll
* ���:�̺�Ʈ�� �´� ��ũ�� �׼��� ���Ѵ�. 
*/
void VerticalThumbTrack::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	if (nPos != this->notepannel->clientLocation->lineOrder) {//�ǽð� ��ũ���� ������ġ�� Ŭ���̾�Ʈ�� ������ġ�� ��ġ���� ������
		this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, nPos);
		this->notepannel->SetScrollPos(SB_VERT, nPos);
		this->notepannel->Notify();
		this->notepannel->Invalidate(TRUE);
		this->notepannel->caret->ShowCaret();
	}
}
