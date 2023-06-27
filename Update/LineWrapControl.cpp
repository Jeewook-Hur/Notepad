//LineWrapControl.cpp
/*
* 파일명칭:LineWrapControl.cpp
* 기능:자동 줄바꿈을 조정하는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/9/21
*/
#include "LineWrapControl.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "DocumentVirtualSize.h"
#include "CharacterMatrix.h"
#include "Command.h"
#include "CommandCreator.h"
#include "ClientMatrix.h"
#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Select.h"
#include "resource.h"
#include<string>
using namespace std;

/*
* 함수명칭:LineWrapControl
* 기능:생성자
*/
LineWrapControl::LineWrapControl(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~LineWrapControl
* 기능:소멸자
*/
LineWrapControl::~LineWrapControl() {
}

/*
* 함수명칭:Update
* 기능:입력받은 클래스에 맞는 업데이트를 한다.
*/
void LineWrapControl::Update(Subject* theChangedSubject) {
	this->notepannel->isUpdating = TRUE;
	CommandCreator commandCreater(this->notepannel);
	Command* command = NULL;

	UINT lineWrapState = -1;

	if (dynamic_cast<Notepannel*>(theChangedSubject)) {//입력받은 클래스가 메모장이면
		//메뉴의 자동개행클 체크했고 문서를 수정중이며 자동개행을 실행중이 아니면
		lineWrapState = this->notepannel->notepad->cMenu.GetMenuState(IDM_FORMAT_LINEWRAP, MF_BYCOMMAND);
		if (lineWrapState == MF_CHECKED && this->notepannel->documentUploaded == TRUE && this->notepannel->isLineWraping == FALSE) {
			//자동개행 커멘드를 생성한다.
			command = commandCreater.Create(IDM_FORMAT_LINEWRAP);
			//자동개행을 병합 후 다시 개행한다.
			command->UnExecute();
			command->Execute();
			//자동개행 커멘드를 할당 해제한다.
			delete command;
		}
	}
	this->notepannel->isUpdating = FALSE;
}
