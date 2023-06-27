//SelectAllCommand.cpp
/*
* 파일명칭:SelectAllCommand.cpp
* 기능:전체선택하는 커멘드의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#include "SelectAllCommand.h"
#include "Notepannel.h"
#include "Caret.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"

/*
* 함수명칭:SelectAllCommand
* 기능:생성자
*/
SelectAllCommand::SelectAllCommand(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* 함수명칭:~SelectAllCommand
* 기능:소멸자
*/
SelectAllCommand::~SelectAllCommand() {
}

/*
* 함수명칭:Execute
* 기능:복사하기 커멘드를 실행한다.
*/
void SelectAllCommand::Execute() {
	Glyph* currentLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;

	//문서의 맨 뒤로 이동한다. 
	lineOrder = this->notepannel->paper->Last();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->Last();
	//선택하기를 현재 위치로 초기화한다.
	delete this->notepannel->select;
	this->notepannel->select = new Select(notepannel);
	//선택하기를 현재 위치로 이동한다.
	this->notepannel->select->MoveCurrent(charIndex, lineOrder);
	//선택되었다는 표시를 올린다.
	this->notepannel->isSelected = TRUE;
	//업데이트를 한다 
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//클라이언트를 갱신한다.
	this->notepannel->Invalidate(TRUE);
	//캐럿을 보이게한다.
	this->notepannel->caret->ShowCaret();
}