//CtrlZeroKey.cpp
/*
* 파일명칭:CtrlZeroKey.cpp
* 기능:ctrl과 0키를 눌렀을때의 전략
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#include "CtrlZeroKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"

/*
* 함수명칭:CtrlZeroKey
* 기능:생성자
*/
CtrlZeroKey::CtrlZeroKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~CtrlZeroKey
* 기능:소멸자
*/
CtrlZeroKey::~CtrlZeroKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void CtrlZeroKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	//입력받은 메뉴에 맞는 커멘드를 만든다.
	command = commandCreator.Create(IDM_FORMAT_RESTOREDEFALTZOOM);
	if (command != NULL) { //커멘트가 반환되었을경우
		command->Execute();
	}
	delete command;
}