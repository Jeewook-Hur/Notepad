//CtrlAKey.cpp
/*
* 파일명칭:CtrlAKey.cpp
* 기능:ctrl과 A키를 눌렀을때의 전략
* 작성자:허지욱
* 작성일자:2022/11/15
*/
#include "CtrlAKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"

#if 0
#include "Caret.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"
#endif

/*
* 함수명칭:CtrlAKey
* 기능:생성자
*/
CtrlAKey::CtrlAKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~CtrlAKey
* 기능:소멸자
*/
CtrlAKey::~CtrlAKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void CtrlAKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	//입력받은 메뉴에 맞는 커멘드를 만든다.
	command = commandCreator.Create(IDM_FORMAT_SELECTALL);
	if (command != NULL) { //커멘트가 반환되었을경우
		command->Execute();
	}
	delete command;
#if 0
	Glyph* currentLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;

	//문서의 맨 뒤로 이동한다. 
	lineOrder = this->notepannel->paper->Last();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->Last();
	//선택하기를 현재 위치로 초기화한다.
	delete this->notepannel->select;
	this->notepannel->select = new Select(notepannel);
	//선택하기를 현재 위치로 이동한다.
	this->notepannel->select->MoveCurrent(charIndex, lineOrder);
	//선택되었다는 표시를 올린다.
	this->notepannel->isSelected = TRUE;
	//업데이트를 한다 
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//클라이언트를 갱신한다.
	this->notepannel->Invalidate(TRUE);
	//캐럿을 보이게한다.
	this->notepannel->caret->ShowCaret();
#endif
}