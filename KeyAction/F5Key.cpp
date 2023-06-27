//F5Key.cpp
/*
* ���ϸ�Ī:F5Key.cpp
* ���:F5Ű�� ���������� ����
* �ۼ���:������
* �ۼ�����:2023/1/31
*/
#include "F5Key.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"

/*
* �Լ���Ī:F5Key
* ���:������
*/
F5Key::F5Key(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~F5Key
* ���:�Ҹ���
*/
F5Key::~F5Key() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void F5Key::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;

	//�Է¹��� �޴��� �´� Ŀ��带 �����.
	command = commandCreator.Create(IDM_FORMAT_DATE);
	if (command != NULL) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
		command->Execute();
	}
	delete command;
}