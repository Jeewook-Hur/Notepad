//CtrlVKey.cpp
/*
* ���ϸ�Ī:CtrlVKey.cpp
* ���:ctrl�� VŰ�� ���������� ����
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#include "CtrlVKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"
#include "Clipboard.h"
#include "MacroCommand.h"

/*
* �Լ���Ī:CtrlVKey
* ���:������
*/
CtrlVKey::CtrlVKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlVKey
* ���:�Ҹ���
*/
CtrlVKey::~CtrlVKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlVKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;

	if (this->notepannel->clipboard->Check()) { //Ŭ�����忡 ������ ���� ���
		//�Է¹��� �޴��� �´� Ŀ��带 �����.
		command = commandCreator.Create(IDM_FORMAT_PASTE);
		if (command != NULL) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
			command->Execute();
		}
		this->notepannel->macroCommand->Add(command, 1);
		//delete command;
	}
}