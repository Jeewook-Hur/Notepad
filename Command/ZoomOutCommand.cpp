//ZoomOutCommand.cpp
/*
* ���ϸ�Ī:ZoomOutCommand.cpp
* ���:ȭ�� ����ϱ� �޴��� ���� ���(Command)
* �ۼ���:������
* �ۼ�����:20221007
*/
#include "ZoomOutCommand.h"
#include "Notepannel.h"
#include "Zoomer.h"
#include "CharacterMatrix.h"
#include "ClientMatrix.h"
#include "Caret.h"

/*
* �Լ���Ī:ZoomOutCommand
* ���:������
*/
ZoomOutCommand::ZoomOutCommand(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~ZoomOutCommand
* ���:�Ҹ���
*/
ZoomOutCommand::~ZoomOutCommand() {
}

/*
* �Լ���Ī:Execute
* ���:�����Ѵ�.
*/
void ZoomOutCommand::Execute() {
	//���� ������ Ȯ���Ѵ�.
	int currentMagnification = this->notepannel->zoomer->magnification;
	//�ٲ� ������ ����� �����Ѵ�.
	currentMagnification = currentMagnification - 10;
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