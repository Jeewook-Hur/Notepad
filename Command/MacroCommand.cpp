//MacroCommand.cpp
/*
* 파일명칭:MacroCommand.cpp
* 기능:커멘드를 스택형태로 저장하여 실행취소와 재실행을 실행한다.
* 작성자:허지욱
* 작성일자:2022/11/29
*/
#include "MacroCommand.h"

/*
* 함수명칭:MacroCommand
* 기능:생성자
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
* 함수명칭:~MacroCommand
* 기능:소멸자
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
* 함수명칭:Add
* 기능:커멘드를 더한다.
*/
void MacroCommand::Add(Command* command, int flag) {
	Command* temp = 0;
	//재실행 스택을 비운다. 
	while (this->next->IsEmpty() == false) {
		temp = this->next->Pop();
		delete temp;
	}
	//재실행 플래그 스택을 비운다. 
	while (this->nextFlag->IsEmpty() == false) {
		this->nextFlag->Pop();
	}
	this->previous->Push(command);
	this->previousFlag->Push(flag);
	this->order++;
}

/*
* 함수명칭:Undo
* 기능:실행취소를 한다. 
*/
int MacroCommand::Undo() {
	Command* command = 0;
	int flag = 0;
	int previousFlag = -1;

	if (this->previous->IsEmpty() == false) {
		//기존 되돌리기
		//이전 명령을 가져온다.
		command = this->previous->Pop();
		this->order--;
		//이전 명령을 실행취소한다.
		command->UnExecute();
		//이전 명령을 기억한다. 
		this->next->Push(command);
		//이전 플래그를 가져온다.
		flag = this->previousFlag->Pop();
		//이전 플래그를 기억한다. 
		this->nextFlag->Push(flag);

		//이전 되돌리기 미리보기
		//이전 플래그를 본다.
		previousFlag = this->previousFlag->Peek();
	}

	while (this->previous->IsEmpty() == false && previousFlag == 0) { //플래그가 내려간 동안 반복한다. 
		//이전 명령을 가져온다.
		command = this->previous->Pop();
		this->order--;
		//이전 명령을 실행취소한다.
		command->UnExecute();
		//이전 명령을 기억한다. 
		this->next->Push(command);

		//이전 플래그를 가져온다.
		flag = this->previousFlag->Pop();
		//이전 플래그를 기억한다. 
		this->nextFlag->Push(flag);

		//그 이전 플래그를 본다
		previousFlag = this->previousFlag->Peek();
	}

	int ret = 0;
	if (this->order == this->savePoint) {
		ret = 1;
	}
	return ret;
}

/*
* 함수명칭:Redo
* 기능:재실행을 한다.
*/
int MacroCommand::Redo() {
	Command* command = 0;
	int flag = 0;
	int nextFlag = -1;

	if (this->next->IsEmpty() == false) { //다음 커멘드가 있음면
	//다음 플래그 내용을 본다.
		nextFlag = this->nextFlag->Peek();
	}

	while (this->next->IsEmpty() == false && nextFlag == 0) { //플래그가 내려간 동안 반복한다. 
		//다음 명령을 가져온다.
		command = this->next->Pop();
		this->order++;
		//다음 명령을 실행한다.
		command->Execute();
		//다음 명령을 기억한다.
		this->previous->Push(command);

		//다음 플래그를 가져온다. 
		flag = this->nextFlag->Pop();
		//다음 플래그를 기억한다.
		this->previousFlag->Push(flag);

		//그 다음 플래그 내용을 본다.
		nextFlag = this->nextFlag->Peek();
	}

	if (this->next->IsEmpty() == false) { //다음 커멘드가 있음면
		//다음 명령을 가져온다.
		command = this->next->Pop();
		this->order++;
		//다음 명령을 실행한다.
		command->Execute();
		//다음 명령을 기억한다.
		this->previous->Push(command);

		//다음 플래그를 가져온다. 
		flag = this->nextFlag->Pop();
		//다음 플래그를 기억한다.
		this->previousFlag->Push(flag);
	}
	int ret = 0;
	if (this->order == this->savePoint) {
		ret = 1;
	}
	return ret;
}

/*
* 함수명칭:ToUndo
* 기능:실행취소가 가능한지 확인한다.
*/
bool MacroCommand::ToUndo() {
	bool ret = false;
	if (this->previous->IsEmpty() == false) {
		ret = true;
	}
	return ret;
}

/*
* 함수명칭:ToRedo
* 기능:재실행이 가능한지 확인한다.
*/
bool MacroCommand::ToRedo() {
	bool ret = false;
	if (this->next->IsEmpty() == false) {
		ret = true;
	}
	return ret;
}

/*
* 함수명칭:FlagOn
* 기능:마지막 실행 커멘드의 플래그를 올린다.
*/
void MacroCommand::FlagUp(){
	int flag;
	flag = this->previousFlag->Pop();
	flag = 1;
	this->previousFlag->Push(flag);
}

/*
* 함수명칭:FlagDown
* 기능:마지막 실행 커멘드의 플래그를 내린다.
*/
void MacroCommand::FlagDown() {
	int flag;
	flag = this->previousFlag->Pop();
	flag = 0;
	this->previousFlag->Push(flag);
}

/*
* 함수명칭:ChangeSavePoint
* 기능:저장지점을 바꾼다. 
*/
int MacroCommand::ChangeSavePoint() {
	this->savePoint = this->order;
	return this->savePoint;
}