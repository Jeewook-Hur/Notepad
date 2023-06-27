//RestoreDefaultZoomCommand.cpp
/*
* ���ϸ�Ī:RestoreDefaultZoomCommand.cpp
* ���:ȭ�� Ȯ��/����ϱ� �⺻�� ���� �޴��� ���� ���(Command)
* �ۼ���:������
* �ۼ�����:20221007
*/
#include "RestoreDefaultZoomCommand.h"
#include "Notepannel.h"
#include "Zoomer.h"
#include "CharacterMatrix.h"
#include "ClientMatrix.h"
#include "Caret.h"

/*
* �Լ���Ī:RestoreDefaultZoomCommand
* ���:������
*/
RestoreDefaultZoomCommand::RestoreDefaultZoomCommand(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~RestoreDefaultZoomCommand
* ���:�Ҹ���
*/
RestoreDefaultZoomCommand::~RestoreDefaultZoomCommand() {
}

/*
* �Լ���Ī:Execute
* ���:�����Ѵ�.
*/
void RestoreDefaultZoomCommand::Execute() {
	//���� ������ Ȯ���Ѵ�.
	int currentMagnification = this->notepannel->zoomer->magnification;
	//�ٲ� ������ ����� �����Ѵ�.
	currentMagnification = 100;
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