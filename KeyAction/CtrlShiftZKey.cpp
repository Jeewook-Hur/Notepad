//CtrlShiftZKey.cpp
/*
* 파일명칭:CtrlShiftZKey.cpp
* 기능:ctrl과 shift와 Z키를 눌렀을때의 전략
* 작성자:허지욱
* 작성일자:2022/11/29
*/
#include "CtrlShiftZKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"

/*
* 함수명칭:CtrlShiftZKey
* 기능:생성자
*/
CtrlShiftZKey::CtrlShiftZKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~CtrlShiftZKey
* 기능:소멸자
*/
CtrlShiftZKey::~CtrlShiftZKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void CtrlShiftZKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	//입력받은 메뉴에 맞는 커멘드를 만든다.
	command = commandCreator.Create(IDM_FORMAT_UNDO);
	if (command != NULL) { //커멘트가 반환되었을경우
		command->UnExecute();
	}
	delete command;
}