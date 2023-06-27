//CtrlZKey.cpp
/*
* ���ϸ�Ī:CtrlZKey.cpp
* ���:ctrl�� ZŰ�� ���������� ����
* �ۼ���:������
* �ۼ�����:2022/11/29
*/
#include "CtrlZKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"

/*
* �Լ���Ī:CtrlZKey
* ���:������
*/
CtrlZKey::CtrlZKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlZKey
* ���:�Ҹ���
*/
CtrlZKey::~CtrlZKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlZKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	//�Է¹��� �޴��� �´� Ŀ��带 �����.
	command = commandCreator.Create(IDM_FORMAT_UNDO);
	if (command != NULL) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
		command->Execute();
	}
	delete command;
}