//StatusBarControl.cpp
/*
* 파일명칭:StatusBarControl.cpp
* 기능:상태표시줄을 조정하는 클래스
* 작성자:허지욱
* 작성일자:2023/1/8
*/
#include "StatusBarControl.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "StatusBar.h"

/*
* 함수명칭:StatusBarControl
* 기능:생성자
*/
StatusBarControl::StatusBarControl(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~StatusBarControl
* 기능:소멸자
*/
StatusBarControl::~StatusBarControl() {
}

/*
* 함수명칭:Update
* 기능:입력받은 클래스에 맞는 업데이트를 한다.
*/
void StatusBarControl::Update(Subject* theChangedSubject) {

	if (dynamic_cast<Notepannel*>(theChangedSubject)) {//입력받은 클래스가 메모장이면
		//상태표시줄을 업데이트 한다.
		this->notepannel->notepad->statusBar->UpdateStatusBar();
	}
	this->notepannel->isUpdating = FALSE;
}
