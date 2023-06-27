//ZoomOutCommand.cpp
/*
* 파일명칭:ZoomOutCommand.cpp
* 기능:화면 축소하기 메뉴에 대한 명령(Command)
* 작성자:허지욱
* 작성일자:20221007
*/
#include "ZoomOutCommand.h"
#include "Notepannel.h"
#include "Zoomer.h"
#include "CharacterMatrix.h"
#include "ClientMatrix.h"
#include "Caret.h"

/*
* 함수명칭:ZoomOutCommand
* 기능:생성자
*/
ZoomOutCommand::ZoomOutCommand(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* 함수명칭:~ZoomOutCommand
* 기능:소멸자
*/
ZoomOutCommand::~ZoomOutCommand() {
}

/*
* 함수명칭:Execute
* 기능:실행한다.
*/
void ZoomOutCommand::Execute() {
	//현재 배율을 확인한다.
	int currentMagnification = this->notepannel->zoomer->magnification;
	//바꿀 배율을 만들어 갱신한다.
	currentMagnification = currentMagnification - 10;
	this->notepannel->zoomer->Change(currentMagnification);
	//배율로 영향받는 함수들을 갱신한다
	delete this->notepannel->characterMatrix;
	this->notepannel->characterMatrix = new CharacterMatrix(this->notepannel);
	delete this->notepannel->clientMatrix;
	this->notepannel->clientMatrix = new ClientMatrix(this->notepannel);
	//업데이트를 한다
	this->notepannel->documentUploaded = TRUE;
	this->notepannel->Notify();
	//클라이언트를 갱신한다.
	this->notepannel->Invalidate(TRUE);

	//캐럿을 표시한다.
	this->notepannel->caret->ShowCaret();
}