//PrintCommand.cpp
/*
* 파일명칭:PrintCommand.cpp
* 기능:인쇄 커멘드
* 작성자:허지욱
* 작성일자:2022/12/19
*/
#include "PrintCommand.h"
#include "Notepannel.h"
#include "PreviewPage.h"
#include <afxdlgs.h>

/*
* 함수명칭:PrintCommand
* 기능:생성자
*/
PrintCommand::PrintCommand(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~PrintCommand
* 기능:소멸자
*/
PrintCommand::~PrintCommand() {
}

/*
* 함수명칭:Execute
* 기능:커멘드를 실행하다
*/
void PrintCommand::Execute() {
	PreviewPage* previewPage;
	HDC hPrinter;
	RECT pageSize = { 0, 0, 700, 950 };
	//인쇄하기 일반대화상자를 만든다.
	CPrintDialogEx printDialogEx(PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS |  PD_NOSELECTION | PD_NOCURRENTPAGE, this->notepannel);
	//인쇄하기 일반대화상자를 띄운다. 
	printDialogEx.DoModal();

	if (printDialogEx.m_pdex.dwResultAction == PD_RESULT_PRINT) { //인쇄하기를 눌렀을 경우
		//인쇄를 한다.
		//프린터의 디바이스 컨텍스트를 가져온다. 
		hPrinter = printDialogEx.CreatePrinterDC();

		previewPage = new PreviewPage(this->notepannel);

		//미리보기 페이지를 만든다. 
		previewPage->Create(NULL, "페이지 미리보기", WS_OVERLAPPEDWINDOW, pageSize, this->notepannel);
		//인쇄한다. 
		previewPage->Print(hPrinter);
		//미리보기 윈도우를 띄운다. 
		//previewPage->ShowWindow(SW_SHOW);//MAXIMIZED);
		//previewPage->UpdateWindow();
		
		//인쇄를 마치면 미리보기 클래스를 할당해제한다. 
		//인쇄를 마치면 핸들을 제거한다.
		DeleteDC(hPrinter);
	}
}