//CtrlHKey.cpp
/*
* ���ϸ�Ī:CtrlHKey.cpp
* ���:ctrl�� HŰ�� ���������� ����
* �ۼ���:������
* �ۼ�����:2022/12/8
*/
#include "CtrlHKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"

/*
* �Լ���Ī:CtrlHKey
* ���:������
*/
CtrlHKey::CtrlHKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlHKey
* ���:�Ҹ���
*/
CtrlHKey::~CtrlHKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlHKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	//�Է¹��� �޴��� �´� Ŀ��带 �����.
	command = commandCreator.Create(IDM_FORMAT_REPLACE);
	if (command != NULL) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
		command->Execute();
		delete command;
	}
	//delete command;
}