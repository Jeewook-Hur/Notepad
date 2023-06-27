//ZoomInCommand.cpp
/*
* ���ϸ�Ī:ZoomInCommand.cpp
* ���:ȭ�� Ȯ���ϱ� �޴��� ���� ���(Command)
* �ۼ���:������
* �ۼ�����:20221007
*/
#include "ZoomInCommand.h"
#include "Notepannel.h"
#include "Zoomer.h"
#include "CharacterMatrix.h"
#include "ClientMatrix.h"
#include "Caret.h"

/*
* �Լ���Ī:ZoomInCommand
* ���:������
*/
ZoomInCommand::ZoomInCommand(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~ZoomInCommand
* ���:�Ҹ���
*/
ZoomInCommand::~ZoomInCommand() {
}

/*
* �Լ���Ī:Execute
* ���:�����Ѵ�.
*/
void ZoomInCommand::Execute() {

	//���� ������ Ȯ���Ѵ�.
	int currentMagnification = this->notepannel->zoomer->magnification; 
	//�ٲ� ������ ����� �����Ѵ�.
	currentMagnification = currentMagnification + 10;
	this->notepannel->zoomer->Change(currentMagnification);
	//������ ����޴� �Լ����� �����Ѵ�
	delete this->notepannel->characterMatrix;
	this->notepannel->characterMatrix = new CharacterMatrix(this->notepannel);
	delete this->notepannel->clientMatrix;
	this->notepannel->clientMatrix = new ClientMatrix(this->notepannel);
	//������Ʈ�� �Ѵ�
	this->notepannel->documentUploaded = TRUE;
	this->notepannel->Notify();
	//Ŭ���̾�Ʈ�� �����Ѵ�.
	this->notepannel->Invalidate(TRUE);
	
	//ĳ���� ǥ���Ѵ�.
	this->notepannel->caret->ShowCaret();
}