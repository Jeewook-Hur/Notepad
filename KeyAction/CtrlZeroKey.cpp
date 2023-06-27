//CtrlZeroKey.cpp
/*
* ���ϸ�Ī:CtrlZeroKey.cpp
* ���:ctrl�� 0Ű�� ���������� ����
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#include "CtrlZeroKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"

/*
* �Լ���Ī:CtrlZeroKey
* ���:������
*/
CtrlZeroKey::CtrlZeroKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlZeroKey
* ���:�Ҹ���
*/
CtrlZeroKey::~CtrlZeroKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlZeroKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	//�Է¹��� �޴��� �´� Ŀ��带 �����.
	command = commandCreator.Create(IDM_FORMAT_RESTOREDEFALTZOOM);
	if (command != NULL) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
		command->Execute();
	}
	delete command;
}