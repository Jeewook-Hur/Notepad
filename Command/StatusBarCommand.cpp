//StatusBarCommand.cpp
/*
* 파일명칭:StatusBarCommand.cpp
* 기능:상태표시줄 메뉴
* 작성자:허지욱
* 작성일자:20220920
*/
#include "StatusBarCommand.h"
#include "Notepad.h"
#include "Notepannel.h"
#include "StatusBar.h"
#include "Scroll.h"

/*
* 함수명칭:StatusBarCommand
* 기능:생성자
*/
StatusBarCommand::StatusBarCommand(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* 함수명칭:StatusBarCommand
* 기능:소멸자
*/
StatusBarCommand::~StatusBarCommand() {
}

/*
* 함수명칭:Execute
* 기능:자동 줄 바꿈 커멘드를 실행한다.
*/
void StatusBarCommand::Execute() { 
	WINDOWINFO windowInfo{ 0, };
	//상태표시줄을 표시한다. 
	this->notepannel->notepad->statusBar->ShowStatusBar();
	//패널의 크기를 갱신한다. 
	//클라이언트의 정보를 가져온다.
	this->notepannel->notepad->GetWindowInfo(&windowInfo);
	CRect windowRect = windowInfo.rcClient;
	//클라이언트 크기에 맞게 패널 크기를 갱신한다.
	CRect pannelRect = { 0,0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top - this->notepannel->notepad->statusBar->heigth };
	this->notepannel->isUpdating = TRUE;
	this->notepannel->MoveWindow(&pannelRect);
	this->notepannel->isUpdating = FALSE;

	//업데이트를 한다.
	this->notepannel->documentUploaded = TRUE;
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//패널을 갱신한다.
	this->notepannel->Invalidate(TRUE);
}

/*
* 함수명칭:UnExecute
* 기능:자동 줄 바꿈 커멘드를 실행한다.
*/
void StatusBarCommand::UnExecute() {
	WINDOWINFO windowInfo{ 0, };
	
	//상태표시줄을 숨긴다.
	this->notepannel->notepad->statusBar->HideStatusBar();
	//패널의 크기를 갱신한다. 
	//클라이언트의 정보를 가져온다.
	this->notepannel->notepad->GetWindowInfo(&windowInfo);
	CRect windowRect = windowInfo.rcClient;
	//클라이언트 크기에 맞게 패널 크기를 갱신한다.
	CRect pannelRect = { 0 , 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top };

	this->notepannel->isUpdating = TRUE;
	this->notepannel->MoveWindow(&pannelRect);
	this->notepannel->isUpdating = FALSE;
	
	//업데이트를 한다.
	this->notepannel->documentUploaded = TRUE;
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();

	//패널을 갱신한다.
	this->notepannel->Invalidate(TRUE);
}