//CtrlWheelDown.cpp
/*
* ���ϸ�Ī:CtrlWheelDown.cpp
* ���:��Ʈ���� �������¿��� ���콺 ���� �Ʒ��� ���������� �̺�Ʈ�� �����ϴ� Ŭ����
* �ۼ���:������
* �ۼ�����:2022/10/12
*/
#include "CtrlWheelDown.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"


/*
* �Լ���Ī:CtrlWheelDown
* ���:������
*/
CtrlWheelDown::CtrlWheelDown(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlWheelDown
* ���:�Ҹ���
*/
CtrlWheelDown::~CtrlWheelDown() {
}

/*
* �Լ���Ī:OnMouseWheel
* ���:�ٿ� ������ ���� �̺�Ʈ�� �����Ѵ�.
*/
BOOL CtrlWheelDown::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	Command* command = 0;
	CommandCreator commandCreator(this->notepannel);
	command = commandCreator.Create(IDM_FORMAT_ZOOMOUT);
	command->Execute();
	delete command;
	return TRUE;
}