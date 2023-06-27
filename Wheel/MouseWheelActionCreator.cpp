//MouseWheelActionCreator.cpp
/*
* ���ϸ�Ī:MouseWheelActionCreator.cpp
* ���:���콺 �� �׼� ���� ���丮
* �ۼ���:������
* �ۼ�����:2022/10/12
*/
#include "MouseWheelActionCreator.h"
#include "Notepannel.h"
#include "WheelUp.h"
#include "CtrlWheelUp.h"
#include "WheelDown.h"
#include "CtrlWheelDown.h"


/*
* �Լ���Ī:MouseWheelActionCreator
* ���:������
*/
MouseWheelActionCreator::MouseWheelActionCreator(Notepannel* notepannel)
	:notepannel(notepannel) {
}

/*
* �Լ���Ī:~MouseWheelActionCreator
* ���:�Ҹ���
*/
MouseWheelActionCreator::~MouseWheelActionCreator() {
}

/*
* �Լ���Ī:Create
* ���:�Է¹��� ��ɿ� �°� �Լ��� �����Ѵ�.
*/
MouseWheelAction* MouseWheelActionCreator::Create(UINT nFlags, short zDelta, CPoint pt) {
	MouseWheelAction* mouseWheelAction = 0;
	SHORT ctrlKeyState = GetKeyState(VK_CONTROL);

	
	if (zDelta > 0 && !(ctrlKeyState & 0x8000)) {
		mouseWheelAction = new WheelUp(this->notepannel);
	}
	else if (zDelta > 0 && (ctrlKeyState & 0x8000)) {
		mouseWheelAction = new CtrlWheelUp(this->notepannel);
	}
	else if (zDelta < 0 && !(ctrlKeyState & 0x8000)) {
		mouseWheelAction = new WheelDown(this->notepannel);
	}
	else if (zDelta < 0 && (ctrlKeyState & 0x8000)) {
		mouseWheelAction = new CtrlWheelDown(this->notepannel);
	}
#if 0
	else if () {
	}
#endif

	return mouseWheelAction;
}