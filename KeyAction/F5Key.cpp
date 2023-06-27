//F5Key.cpp
/*
* 파일명칭:F5Key.cpp
* 기능:F5키를 눌렀을때의 전략
* 작성자:허지욱
* 작성일자:2023/1/31
*/
#include "F5Key.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"

/*
* 함수명칭:F5Key
* 기능:생성자
*/
F5Key::F5Key(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~F5Key
* 기능:소멸자
*/
F5Key::~F5Key() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void F5Key::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;

	//입력받은 메뉴에 맞는 커멘드를 만든다.
	command = commandCreator.Create(IDM_FORMAT_DATE);
	if (command != NULL) { //커멘트가 반환되었을경우
		command->Execute();
	}
	delete command;
}