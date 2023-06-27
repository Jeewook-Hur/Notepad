//CtrlShiftZKey.cpp
/*
* ���ϸ�Ī:CtrlShiftZKey.cpp
* ���:ctrl�� shift�� ZŰ�� ���������� ����
* �ۼ���:������
* �ۼ�����:2022/11/29
*/
#include "CtrlShiftZKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"

/*
* �Լ���Ī:CtrlShiftZKey
* ���:������
*/
CtrlShiftZKey::CtrlShiftZKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlShiftZKey
* ���:�Ҹ���
*/
CtrlShiftZKey::~CtrlShiftZKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlShiftZKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	//�Է¹��� �޴��� �´� Ŀ��带 �����.
	command = commandCreator.Create(IDM_FORMAT_UNDO);
	if (command != NULL) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
		command->UnExecute();
	}
	delete command;
}