//LineWrapControl.cpp
/*
* ���ϸ�Ī:LineWrapControl.cpp
* ���:�ڵ� �ٹٲ��� �����ϴ� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/9/21
*/
#include "LineWrapControl.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "DocumentVirtualSize.h"
#include "CharacterMatrix.h"
#include "Command.h"
#include "CommandCreator.h"
#include "ClientMatrix.h"
#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Select.h"
#include "resource.h"
#include<string>
using namespace std;

/*
* �Լ���Ī:LineWrapControl
* ���:������
*/
LineWrapControl::LineWrapControl(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~LineWrapControl
* ���:�Ҹ���
*/
LineWrapControl::~LineWrapControl() {
}

/*
* �Լ���Ī:Update
* ���:�Է¹��� Ŭ������ �´� ������Ʈ�� �Ѵ�.
*/
void LineWrapControl::Update(Subject* theChangedSubject) {
	this->notepannel->isUpdating = TRUE;
	CommandCreator commandCreater(this->notepannel);
	Command* command = NULL;

	UINT lineWrapState = -1;

	if (dynamic_cast<Notepannel*>(theChangedSubject)) {//�Է¹��� Ŭ������ �޸����̸�
		//�޴��� �ڵ�����Ŭ üũ�߰� ������ �������̸� �ڵ������� �������� �ƴϸ�
		lineWrapState = this->notepannel->notepad->cMenu.GetMenuState(IDM_FORMAT_LINEWRAP, MF_BYCOMMAND);
		if (lineWrapState == MF_CHECKED && this->notepannel->documentUploaded == TRUE && this->notepannel->isLineWraping == FALSE) {
			//�ڵ����� Ŀ��带 �����Ѵ�.
			command = commandCreater.Create(IDM_FORMAT_LINEWRAP);
			//�ڵ������� ���� �� �ٽ� �����Ѵ�.
			command->UnExecute();
			command->Execute();
			//�ڵ����� Ŀ��带 �Ҵ� �����Ѵ�.
			delete command;
		}
	}
	this->notepannel->isUpdating = FALSE;
}
