//CtrlFKey.cpp
/*
* ���ϸ�Ī:CtrlFKey.cpp
* ���:ctrl�� FŰ�� ���������� ����
* �ۼ���:������
* �ۼ�����:2022/12/7
*/
#include "CtrlFKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"
#include "Paper.h"

/*
* �Լ���Ī:CtrlFKey
* ���:������
*/
CtrlFKey::CtrlFKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlFKey
* ���:�Ҹ���
*/
CtrlFKey::~CtrlFKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlFKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long charNumber;
	//���̿� ������ �ִ��� Ȯ���Ѵ�. 
	charNumber = this->notepannel->paper->GetCharNumber();

	if (charNumber > 0) { //���̿� ������ ������ 
		CommandCreator commandCreator(this->notepannel);
		Command* command = NULL;
		//�Է¹��� �޴��� �´� Ŀ��带 �����.
		command = commandCreator.Create(IDM_FORMAT_FIND);
		if (command != NULL) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
			command->Execute();
			delete command;
		}
		//delete command;
	}
}