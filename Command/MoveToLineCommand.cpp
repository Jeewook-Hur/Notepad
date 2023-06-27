//MoveToLineCommand.cpp
/*
* ���ϸ�Ī:MoveToLineCommand.cpp
* ���:�� �̵� �޴�
* �ۼ���:������
* �ۼ�����:2023/2/6
*/
#include "MoveToLineCommand.h"
#include "Notepannel.h"
#include "MoveToLineForm.h"

/*
* �Լ���Ī:MoveToLineCommand
* ���:������
*/
MoveToLineCommand::MoveToLineCommand(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~MoveToLineCommand
* ���:�Ҹ���
*/
MoveToLineCommand::~MoveToLineCommand() {
}

/*
* �Լ���Ī:Execute
* ���:Ŀ��带 �����ϴ�
*/
void MoveToLineCommand::Execute() {
	MoveToLineForm moveToLineForm(this->notepannel, this->notepannel);
	moveToLineForm.DoModal();
}