//CtrlVKey.cpp
/*
* 파일명칭:CtrlVKey.cpp
* 기능:ctrl과 V키를 눌렀을때의 전략
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#include "CtrlVKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"
#include "Clipboard.h"
#include "MacroCommand.h"

/*
* 함수명칭:CtrlVKey
* 기능:생성자
*/
CtrlVKey::CtrlVKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~CtrlVKey
* 기능:소멸자
*/
CtrlVKey::~CtrlVKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void CtrlVKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;

	if (this->notepannel->clipboard->Check()) { //클립보드에 내용이 있을 경우
		//입력받은 메뉴에 맞는 커멘드를 만든다.
		command = commandCreator.Create(IDM_FORMAT_PASTE);
		if (command != NULL) { //커멘트가 반환되었을경우
			command->Execute();
		}
		this->notepannel->macroCommand->Add(command, 1);
		//delete command;
	}
}