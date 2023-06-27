//CtrlXKey.cpp
/*
* ���ϸ�Ī:CtrlXKey.cpp
* ���:ctrl�� XŰ�� ���������� ����
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#include "CtrlXKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"
#include "MacroCommand.h"

/*
* �Լ���Ī:CtrlXKey
* ���:������
*/
CtrlXKey::CtrlXKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlXKey
* ���:�Ҹ���
*/
CtrlXKey::~CtrlXKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlXKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->notepannel->isSelected == TRUE) {
		CommandCreator commandCreator(this->notepannel);
		Command* command = NULL;
		//�Է¹��� �޴��� �´� Ŀ��带 �����.
		command = commandCreator.Create(IDM_FORMAT_CUT);
		if (command != NULL) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
			command->Execute();
		}
		this->notepannel->macroCommand->Add(command, 1);
		//delete command;
	}
}