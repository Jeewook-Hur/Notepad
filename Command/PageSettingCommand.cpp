//PageSettingCommand.cpp
/*
* 파일명칭:PageSettingCommand.cpp
* 기능:페이지설정 커멘드
* 작성자:허지욱
* 작성일자:2022/12/16
*/
#include "PageSettingCommand.h"
#include "Notepannel.h"
#include "PreviewPage.h"
#include "PageSettingForm.h"

/*
* 함수명칭:PageSettingCommand
* 기능:생성자
*/
PageSettingCommand::PageSettingCommand(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~PageSettingCommand
* 기능:소멸자
*/
PageSettingCommand::~PageSettingCommand() {
}

/*
* 함수명칭:Execute
* 기능:커멘드를 실행하다
*/
void PageSettingCommand::Execute() {
	PageSettingForm pageSettingForm(this->notepannel, this->notepannel);
	pageSettingForm.DoModal();
#if 0
	PreviewPage* previewPage = new PreviewPage(this->notepannel); 
	RECT pageSize = { 0, 0, 700, 950 };
	//미리보기 윈도우를 만든다
	previewPage->Create(NULL, "페이지 미리보기", WS_OVERLAPPEDWINDOW, pageSize, this->notepannel);
	//미리보기 윈도우를 띄운다. 
	previewPage->ShowWindow(SW_SHOW);//MAXIMIZED);
	previewPage->UpdateWindow();
#endif
}