//MoveToLineCommand.cpp
/*
* 파일명칭:MoveToLineCommand.cpp
* 기능:줄 이동 메뉴
* 작성자:허지욱
* 작성일자:2023/2/6
*/
#include "MoveToLineCommand.h"
#include "Notepannel.h"
#include "MoveToLineForm.h"

/*
* 함수명칭:MoveToLineCommand
* 기능:생성자
*/
MoveToLineCommand::MoveToLineCommand(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~MoveToLineCommand
* 기능:소멸자
*/
MoveToLineCommand::~MoveToLineCommand() {
}

/*
* 함수명칭:Execute
* 기능:커멘드를 실행하다
*/
void MoveToLineCommand::Execute() {
	MoveToLineForm moveToLineForm(this->notepannel, this->notepannel);
	moveToLineForm.DoModal();
}