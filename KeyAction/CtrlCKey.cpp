//CtrlCKey.cpp
/*
* ���ϸ�Ī:CtrlCKey.cpp
* ���:ctrl�� CŰ�� ���������� ����
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#include "CtrlCKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"

/*
* �Լ���Ī:CtrlCKey
* ���:������
*/
CtrlCKey::CtrlCKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlCKey
* ���:�Ҹ���
*/
CtrlCKey::~CtrlCKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlCKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	
	if (this->notepannel->isSelected == TRUE) { //�������� ���õǾ� �ִ°��
		//�Է¹��� �޴��� �´� Ŀ��带 �����.
		command = commandCreator.Create(IDM_FORMAT_COPY);
		if (command != NULL) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
			command->Execute();
		}
		delete command;
	}
}