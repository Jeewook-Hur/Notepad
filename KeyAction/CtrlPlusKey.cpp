//CtrlPlusKey.cpp
/*
* ���ϸ�Ī:CtrlPlusKey.cpp
* ���:ctrl�� +Ű�� ���������� ����
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#include "CtrlPlusKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"

/*
* �Լ���Ī:CtrlPlusKey
* ���:������
*/
CtrlPlusKey::CtrlPlusKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlPlusKey
* ���:�Ҹ���
*/
CtrlPlusKey::~CtrlPlusKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlPlusKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	//�Է¹��� �޴��� �´� Ŀ��带 �����.
	command = commandCreator.Create(IDM_FORMAT_ZOOMIN);
	if (command != NULL) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
		command->Execute();
	}
	delete command;
}