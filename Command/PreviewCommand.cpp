//PreviewCommand.cpp
/*
* 파일명칭:PreviewCommand.cpp
* 기능:미리보기 커멘드
* 작성자:허지욱
* 작성일자:2022/12/16
*/
#include "PreviewCommand.h"
#include "Notepannel.h"
#include "PreviewPage.h"

/*
* 함수명칭:PreviewCommand
* 기능:생성자
*/
PreviewCommand::PreviewCommand(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~PreviewCommand
* 기능:소멸자
*/
PreviewCommand::~PreviewCommand() {
}

/*
* 함수명칭:Execute
* 기능:커멘드를 실행하다
*/
void PreviewCommand::Execute() {
	PreviewPage* previewPage = new PreviewPage(this->notepannel);
	RECT pageSize = { 0, 0, 700, 950 };
	//미리보기 윈도우를 만든다
	previewPage->Create(NULL, "페이지 미리보기", WS_OVERLAPPEDWINDOW, pageSize, this->notepannel);
	//미리보기 윈도우를 띄운다. 
	previewPage->ShowWindow(SW_SHOW);//MAXIMIZED);
	CRect windowSize = { 0,0, 630, 900 };
	previewPage->MoveWindow(&windowSize);
	previewPage->UpdateWindow();
}