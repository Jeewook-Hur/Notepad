//StatusBarCommand.cpp
/*
* ���ϸ�Ī:StatusBarCommand.cpp
* ���:����ǥ���� �޴�
* �ۼ���:������
* �ۼ�����:20220920
*/
#include "StatusBarCommand.h"
#include "Notepad.h"
#include "Notepannel.h"
#include "StatusBar.h"
#include "Scroll.h"

/*
* �Լ���Ī:StatusBarCommand
* ���:������
*/
StatusBarCommand::StatusBarCommand(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:StatusBarCommand
* ���:�Ҹ���
*/
StatusBarCommand::~StatusBarCommand() {
}

/*
* �Լ���Ī:Execute
* ���:�ڵ� �� �ٲ� Ŀ��带 �����Ѵ�.
*/
void StatusBarCommand::Execute() { 
	WINDOWINFO windowInfo{ 0, };
	//����ǥ������ ǥ���Ѵ�. 
	this->notepannel->notepad->statusBar->ShowStatusBar();
	//�г��� ũ�⸦ �����Ѵ�. 
	//Ŭ���̾�Ʈ�� ������ �����´�.
	this->notepannel->notepad->GetWindowInfo(&windowInfo);
	CRect windowRect = windowInfo.rcClient;
	//Ŭ���̾�Ʈ ũ�⿡ �°� �г� ũ�⸦ �����Ѵ�.
	CRect pannelRect = { 0,0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top - this->notepannel->notepad->statusBar->heigth };
	this->notepannel->isUpdating = TRUE;
	this->notepannel->MoveWindow(&pannelRect);
	this->notepannel->isUpdating = FALSE;

	//������Ʈ�� �Ѵ�.
	this->notepannel->documentUploaded = TRUE;
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//�г��� �����Ѵ�.
	this->notepannel->Invalidate(TRUE);
}

/*
* �Լ���Ī:UnExecute
* ���:�ڵ� �� �ٲ� Ŀ��带 �����Ѵ�.
*/
void StatusBarCommand::UnExecute() {
	WINDOWINFO windowInfo{ 0, };
	
	//����ǥ������ �����.
	this->notepannel->notepad->statusBar->HideStatusBar();
	//�г��� ũ�⸦ �����Ѵ�. 
	//Ŭ���̾�Ʈ�� ������ �����´�.
	this->notepannel->notepad->GetWindowInfo(&windowInfo);
	CRect windowRect = windowInfo.rcClient;
	//Ŭ���̾�Ʈ ũ�⿡ �°� �г� ũ�⸦ �����Ѵ�.
	CRect pannelRect = { 0 , 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top };

	this->notepannel->isUpdating = TRUE;
	this->notepannel->MoveWindow(&pannelRect);
	this->notepannel->isUpdating = FALSE;
	
	//������Ʈ�� �Ѵ�.
	this->notepannel->documentUploaded = TRUE;
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();

	//�г��� �����Ѵ�.
	this->notepannel->Invalidate(TRUE);
}