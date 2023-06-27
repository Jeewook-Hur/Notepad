//CtrlFKey.cpp
/*
* 파일명칭:CtrlFKey.cpp
* 기능:ctrl과 F키를 눌렀을때의 전략
* 작성자:허지욱
* 작성일자:2022/12/7
*/
#include "CtrlFKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"
#include "Paper.h"

/*
* 함수명칭:CtrlFKey
* 기능:생성자
*/
CtrlFKey::CtrlFKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~CtrlFKey
* 기능:소멸자
*/
CtrlFKey::~CtrlFKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void CtrlFKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long charNumber;
	//종이에 내용이 있는지 확인한다. 
	charNumber = this->notepannel->paper->GetCharNumber();

	if (charNumber > 0) { //종이에 내용이 있으면 
		CommandCreator commandCreator(this->notepannel);
		Command* command = NULL;
		//입력받은 메뉴에 맞는 커멘드를 만든다.
		command = commandCreator.Create(IDM_FORMAT_FIND);
		if (command != NULL) { //커멘트가 반환되었을경우
			command->Execute();
			delete command;
		}
		//delete command;
	}
}