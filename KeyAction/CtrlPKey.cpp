//CtrlPKey.cpp
/*
* ���ϸ�Ī:CtrlPKey.cpp
* ���:ctrl�� PŰ�� ���������� ����
* �ۼ���:������
* �ۼ�����:2022/12/19
*/
#include "CtrlPKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"

/*
* �Լ���Ī:CtrlPKey
* ���:������
*/
CtrlPKey::CtrlPKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlPKey
* ���:�Ҹ���
*/
CtrlPKey::~CtrlPKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlPKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	//�Է¹��� �޴��� �´� Ŀ��带 �����.
	command = commandCreator.Create(IDM_FORMAT_PRINT);
	if (command != NULL) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
		command->Execute();
	}
	delete command;
}