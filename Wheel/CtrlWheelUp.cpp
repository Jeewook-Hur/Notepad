//CtrlWheelUp.cpp
/*
* 파일명칭:CtrlWheelUp.cpp
* 기능:컨트롤을 누른상태에서 마우스 휠을 위로 굴렸을때의 이벤트를 수행하는 클래스
* 작성자:허지욱
* 작성일자:2022/10/12
*/
#include "CtrlWheelUp.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"


/*
* 함수명칭:CtrlWheelUp
* 기능:생성자
*/
CtrlWheelUp::CtrlWheelUp(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~CtrlWheelUp
* 기능:소멸자
*/
CtrlWheelUp::~CtrlWheelUp() {
}

/*
* 함수명칭:OnMouseWheel
* 기능:휠울 굴렸을 때의 이벤트를 실행한다.
*/
BOOL CtrlWheelUp::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	Command* command = 0;
	CommandCreator commandCreator(this->notepannel);
	command = commandCreator.Create(IDM_FORMAT_ZOOMIN);
	command->Execute();
	delete command;
	return TRUE;
}