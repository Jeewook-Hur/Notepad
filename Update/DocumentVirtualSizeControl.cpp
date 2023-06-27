//DocumentVirtualSizeControl.cpp
/*
* ���ϸ�Ī:DocumentVirtualSizeControl.cpp
* ���:������ ����ũ�⸦ �����ϴ� Ŭ����
* �ۼ���:������
* �ۼ�����:2022/9/29
*/
#include "DocumentVirtualSizeControl.h"
#include "DocumentVirtualSize.h"
#include "Notepannel.h"

/*
* �Լ���Ī:DocumentVirtualSizeControl
* ���:������
*/
DocumentVirtualSizeControl::DocumentVirtualSizeControl(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~DocumentVirtualSizeControl
* ���:�Ҹ���
*/
DocumentVirtualSizeControl::~DocumentVirtualSizeControl() {
}

/*
* �Լ���Ī:Update
* ���:�Է¹��� Ŭ������ �´� ������Ʈ�� �Ѵ�.
*/
void DocumentVirtualSizeControl::Update(Subject* theChangedSubject) {
	this->notepannel->isUpdating = TRUE;
	if (dynamic_cast<Notepannel*>(theChangedSubject)) {//�Է¹��� Ŭ������ �޸����̸�
		if (this->notepannel->documentUploaded == TRUE) {
			delete this->notepannel->documentVirtualSize;
			this->notepannel->documentVirtualSize = new DocumentVirtualSize(this->notepannel);
		}
	}
	this->notepannel->isUpdating = FALSE;
}
