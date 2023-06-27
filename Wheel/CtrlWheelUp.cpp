//CtrlWheelUp.cpp
/*
* ���ϸ�Ī:CtrlWheelUp.cpp
* ���:��Ʈ���� �������¿��� ���콺 ���� ���� ���������� �̺�Ʈ�� �����ϴ� Ŭ����
* �ۼ���:������
* �ۼ�����:2022/10/12
*/
#include "CtrlWheelUp.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"


/*
* �Լ���Ī:CtrlWheelUp
* ���:������
*/
CtrlWheelUp::CtrlWheelUp(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlWheelUp
* ���:�Ҹ���
*/
CtrlWheelUp::~CtrlWheelUp() {
}

/*
* �Լ���Ī:OnMouseWheel
* ���:�ٿ� ������ ���� �̺�Ʈ�� �����Ѵ�.
*/
BOOL CtrlWheelUp::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	Command* command = 0;
	CommandCreator commandCreator(this->notepannel);
	command = commandCreator.Create(IDM_FORMAT_ZOOMIN);
	command->Execute();
	delete command;
	return TRUE;
}