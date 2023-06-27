//CtrlSKey.cpp
/*
* ���ϸ�Ī:CtrlSKey.cpp
* ���:ctrl�� SŰ�� ���������� ����
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#include "CtrlSKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"

/*
* �Լ���Ī:CtrlSKey
* ���:������
*/
CtrlSKey::CtrlSKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlSKey
* ���:�Ҹ���
*/
CtrlSKey::~CtrlSKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlSKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	//�Է¹��� �޴��� �´� Ŀ��带 �����.
	command = commandCreator.Create(IDM_FORMAT_SAVE);
	if (command != NULL) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
		command->Execute();
	}
	delete command;
}