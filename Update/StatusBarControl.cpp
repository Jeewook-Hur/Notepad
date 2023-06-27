//StatusBarControl.cpp
/*
* ���ϸ�Ī:StatusBarControl.cpp
* ���:����ǥ������ �����ϴ� Ŭ����
* �ۼ���:������
* �ۼ�����:2023/1/8
*/
#include "StatusBarControl.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "StatusBar.h"

/*
* �Լ���Ī:StatusBarControl
* ���:������
*/
StatusBarControl::StatusBarControl(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~StatusBarControl
* ���:�Ҹ���
*/
StatusBarControl::~StatusBarControl() {
}

/*
* �Լ���Ī:Update
* ���:�Է¹��� Ŭ������ �´� ������Ʈ�� �Ѵ�.
*/
void StatusBarControl::Update(Subject* theChangedSubject) {

	if (dynamic_cast<Notepannel*>(theChangedSubject)) {//�Է¹��� Ŭ������ �޸����̸�
		//����ǥ������ ������Ʈ �Ѵ�.
		this->notepannel->notepad->statusBar->UpdateStatusBar();
	}
	this->notepannel->isUpdating = FALSE;
}
