//ScrollInfoControl.cpp
/*
* ���ϸ�Ī:ScrollInfoControl.cpp
* ���:��ũ���� ������ �����ϴ� Ŭ����
* �ۼ���:������
* �ۼ�����:2022/9/29
*/
#include "ScrollInfoControl.h"
#include "Notepannel.h"
#include "Scroll.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"

/*
* �Լ���Ī:ScrollInfoControl
* ���:������
*/
ScrollInfoControl::ScrollInfoControl(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~ScrollInfoControl
* ���:�Ҹ���
*/
ScrollInfoControl::~ScrollInfoControl() {
}

/*
* �Լ���Ī:Update
* ���:�Է¹��� Ŭ������ �´� ������Ʈ�� �Ѵ�.
*/
void ScrollInfoControl::Update(Subject* theChangedSubject) {
	this->notepannel->isUpdating = TRUE;

	int vScrollPosition;
	int hScrollPosition;

	if (dynamic_cast<Notepannel*>(theChangedSubject)) {//�Է¹��� Ŭ������ �޸����̸�
		if (this->notepannel->documentUploaded == TRUE) { //������ �ۼ����̾�����
			//��ũ���� ���� ��ġ�� ���Ѵ�. 
			vScrollPosition = this->notepannel->GetScrollPos(SB_VERT);
			hScrollPosition = this->notepannel->GetScrollPos(SB_HORZ);
			//��ũ���� ���� �� �ʱ�ȭ �Ѵ�.
			delete this->notepannel->scroll;
			this->notepannel->scroll = new Scroll(this->notepannel);
			//��ũ���� ���̰� �پ������� ���� ��ġ�� �����Ѵ�. 
			if (vScrollPosition > this->notepannel->scroll->maxY) {
				vScrollPosition = this->notepannel->scroll->maxY;
				this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder - this->notepannel->clientMatrix->lineNumberInPage + 1);
				//this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, 999999);
				//this->notepannel->scroll->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);
			}
			if (hScrollPosition > this->notepannel->scroll->maxX) {
				hScrollPosition = this->notepannel->scroll->maxX;
				this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);
				//this->notepannel->clientLocation->Move(999999, this->notepannel->clientLocation->lineOrder);
				//this->notepannel->scroll->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);
			}
			//��ũ���� ���� ��ġ�� �̵���Ų��. 
			this->notepannel->SetScrollPos(SB_VERT, vScrollPosition);
			this->notepannel->SetScrollPos(SB_HORZ, hScrollPosition);
			//���� ���� �÷��׸� ������. 
			this->notepannel->documentUploaded = FALSE;
		}
	}
	this->notepannel->isUpdating = FALSE;
}
