//MouseWheelActionCreator.cpp
/*
* 파일명칭:MouseWheelActionCreator.cpp
* 기능:마우스 휠 액션 생성 팩토리
* 작성자:허지욱
* 작성일자:2022/10/12
*/
#include "MouseWheelActionCreator.h"
#include "Notepannel.h"
#include "WheelUp.h"
#include "CtrlWheelUp.h"
#include "WheelDown.h"
#include "CtrlWheelDown.h"


/*
* 함수명칭:MouseWheelActionCreator
* 기능:생성자
*/
MouseWheelActionCreator::MouseWheelActionCreator(Notepannel* notepannel)
	:notepannel(notepannel) {
}

/*
* 함수명칭:~MouseWheelActionCreator
* 기능:소멸자
*/
MouseWheelActionCreator::~MouseWheelActionCreator() {
}

/*
* 함수명칭:Create
* 기능:입력받은 명령에 맞게 함수를 생성한다.
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