//MacroCommand.cpp
/*
* ���ϸ�Ī:MacroCommand.cpp
* ���:Ŀ��带 �������·� �����Ͽ� ������ҿ� ������� �����Ѵ�.
* �ۼ���:������
* �ۼ�����:2022/11/29
*/
#include "MacroCommand.h"

/*
* �Լ���Ī:MacroCommand
* ���:������
*/
MacroCommand::MacroCommand() {
	this->previous = new Stack<Command*>;
	this->next = new Stack<Command*>;
	this->previousFlag = new Stack<int>;
	this->nextFlag = new Stack<int>;
	this->order = 0;
	this->savePoint = 0;
}

/*
* �Լ���Ī:~MacroCommand
* ���:�Ҹ���
*/
MacroCommand::~MacroCommand() {
	Command* command = 0;
	while (this->previous->IsEmpty() == false) {
		command = this->previous->Pop();
		delete command;
	}
	while (this->next->IsEmpty() == false) {
		command = this->next->Pop();
		delete command;
	}
	delete this->previous;
	delete this->next;
	delete this->previousFlag;
	delete this->nextFlag;
}

/*
* �Լ���Ī:Add
* ���:Ŀ��带 ���Ѵ�.
*/
void MacroCommand::Add(Command* command, int flag) {
	Command* temp = 0;
	//����� ������ ����. 
	while (this->next->IsEmpty() == false) {
		temp = this->next->Pop();
		delete temp;
	}
	//����� �÷��� ������ ����. 
	while (this->nextFlag->IsEmpty() == false) {
		this->nextFlag->Pop();
	}
	this->previous->Push(command);
	this->previousFlag->Push(flag);
	this->order++;
}

/*
* �Լ���Ī:Undo
* ���:������Ҹ� �Ѵ�. 
*/
int MacroCommand::Undo() {
	Command* command = 0;
	int flag = 0;
	int previousFlag = -1;

	if (this->previous->IsEmpty() == false) {
		//���� �ǵ�����
		//���� ����� �����´�.
		command = this->previous->Pop();
		this->order--;
		//���� ����� ��������Ѵ�.
		command->UnExecute();
		//���� ����� ����Ѵ�. 
		this->next->Push(command);
		//���� �÷��׸� �����´�.
		flag = this->previousFlag->Pop();
		//���� �÷��׸� ����Ѵ�. 
		this->nextFlag->Push(flag);

		//���� �ǵ����� �̸�����
		//���� �÷��׸� ����.
		previousFlag = this->previousFlag->Peek();
	}

	while (this->previous->IsEmpty() == false && previousFlag == 0) { //�÷��װ� ������ ���� �ݺ��Ѵ�. 
		//���� ����� �����´�.
		command = this->previous->Pop();
		this->order--;
		//���� ����� ��������Ѵ�.
		command->UnExecute();
		//���� ����� ����Ѵ�. 
		this->next->Push(command);

		//���� �÷��׸� �����´�.
		flag = this->previousFlag->Pop();
		//���� �÷��׸� ����Ѵ�. 
		this->nextFlag->Push(flag);

		//�� ���� �÷��׸� ����
		previousFlag = this->previousFlag->Peek();
	}

	int ret = 0;
	if (this->order == this->savePoint) {
		ret = 1;
	}
	return ret;
}

/*
* �Լ���Ī:Redo
* ���:������� �Ѵ�.
*/
int MacroCommand::Redo() {
	Command* command = 0;
	int flag = 0;
	int nextFlag = -1;

	if (this->next->IsEmpty() == false) { //���� Ŀ��尡 ������
	//���� �÷��� ������ ����.
		nextFlag = this->nextFlag->Peek();
	}

	while (this->next->IsEmpty() == false && nextFlag == 0) { //�÷��װ� ������ ���� �ݺ��Ѵ�. 
		//���� ����� �����´�.
		command = this->next->Pop();
		this->order++;
		//���� ����� �����Ѵ�.
		command->Execute();
		//���� ����� ����Ѵ�.
		this->previous->Push(command);

		//���� �÷��׸� �����´�. 
		flag = this->nextFlag->Pop();
		//���� �÷��׸� ����Ѵ�.
		this->previousFlag->Push(flag);

		//�� ���� �÷��� ������ ����.
		nextFlag = this->nextFlag->Peek();
	}

	if (this->next->IsEmpty() == false) { //���� Ŀ��尡 ������
		//���� ����� �����´�.
		command = this->next->Pop();
		this->order++;
		//���� ����� �����Ѵ�.
		command->Execute();
		//���� ����� ����Ѵ�.
		this->previous->Push(command);

		//���� �÷��׸� �����´�. 
		flag = this->nextFlag->Pop();
		//���� �÷��׸� ����Ѵ�.
		this->previousFlag->Push(flag);
	}
	int ret = 0;
	if (this->order == this->savePoint) {
		ret = 1;
	}
	return ret;
}

/*
* �Լ���Ī:ToUndo
* ���:������Ұ� �������� Ȯ���Ѵ�.
*/
bool MacroCommand::ToUndo() {
	bool ret = false;
	if (this->previous->IsEmpty() == false) {
		ret = true;
	}
	return ret;
}

/*
* �Լ���Ī:ToRedo
* ���:������� �������� Ȯ���Ѵ�.
*/
bool MacroCommand::ToRedo() {
	bool ret = false;
	if (this->next->IsEmpty() == false) {
		ret = true;
	}
	return ret;
}

/*
* �Լ���Ī:FlagOn
* ���:������ ���� Ŀ����� �÷��׸� �ø���.
*/
void MacroCommand::FlagUp(){
	int flag;
	flag = this->previousFlag->Pop();
	flag = 1;
	this->previousFlag->Push(flag);
}

/*
* �Լ���Ī:FlagDown
* ���:������ ���� Ŀ����� �÷��׸� ������.
*/
void MacroCommand::FlagDown() {
	int flag;
	flag = this->previousFlag->Pop();
	flag = 0;
	this->previousFlag->Push(flag);
}

/*
* �Լ���Ī:ChangeSavePoint
* ���:���������� �ٲ۴�. 
*/
int MacroCommand::ChangeSavePoint() {
	this->savePoint = this->order;
	return this->savePoint;
}