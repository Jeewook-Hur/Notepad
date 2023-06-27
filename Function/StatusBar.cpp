//StatusBar.cpp
/*
* 파일명칭:StatusBar.cpp
* 기능:상태표시줄 클래스
* 작성자:허지욱
* 작성일자:2023/1/8
*/
#include "StatusBar.h"
#include "Notepad.h"
#include "Notepannel.h"

#include "Zoomer.h"
#include "Paper.h"
#include "Line.h"

/*
* 함수명칭:StatusBar
* 기능:생성자
*/
StatusBar::StatusBar(Notepad* notepad) : notepad(notepad) {
	this->currentLineAndColumn = "Ln 1, Col 1";
	this->currentZoom = "100%";
	this->bytecode = "windowsCRLF";
	this->incoding = "ANSI";

	//상태표시줄을 만든다. 
	this->notepad->statusBarCtrl.Create(WS_CHILD | WS_VISIBLE | CCS_BOTTOM | SBARS_SIZEGRIP, CRect(0, 0, 0, 0), this->notepad, 100002);

	//상태표시줄의 크기를 가져온다. 
	RECT statusBarRect;
	this->notepad->statusBarCtrl.GetRect(0, &statusBarRect);
	this->heigth = statusBarRect.bottom - statusBarRect.top;

	//상태 표시줄을 나눈다. 
	const int parts = 5;
	int widths[parts] = { statusBarRect.right - 550, statusBarRect.right - 400, statusBarRect.right - 300, statusBarRect.right - 100 , -1 };
	this->notepad->statusBarCtrl.SetParts(parts, widths);

	//상태표시줄의 내용을 갱신한다. 
	this->notepad->statusBarCtrl.SetText(this->currentLineAndColumn.c_str(), 1, 0);
	this->notepad->statusBarCtrl.SetText(this->currentZoom.c_str(), 2, 0);
	this->notepad->statusBarCtrl.SetText(this->bytecode.c_str(), 3, 0);
	this->notepad->statusBarCtrl.SetText(this->incoding.c_str(), 4, 0);
}

/*
* 함수명칭:~StatusBar
* 기능:소멸자
*/
StatusBar::~StatusBar() {
}

/*
* 함수명칭:UpdateStatusBar
* 기능:상태표시줄의 텍스트를 갱신한다.
*/
void StatusBar::UpdateStatusBar() {
	WINDOWINFO windowInfo{ 0, };
	CRect windowRect;
	CRect pannelRect;
	Glyph* currentLine;
	Long lineOrder;
	Long charIndex;
	int magnification;

	//클라이언트의 위치를 읽는다.
	this->notepad->GetWindowInfo(&windowInfo);
	windowRect = windowInfo.rcClient;
	//상태표시줄의 크기를 클라이언트에 맞게 조정한다. 
	pannelRect = { 0,windowRect.bottom - this->heigth, windowRect.right - windowRect.left, this->heigth };
	this->notepad->statusBarCtrl.MoveWindow(&pannelRect);

	//상태표시줄의 크기를 가져온다. 
	RECT statusBarRect;
	this->notepad->statusBarCtrl.GetRect(4, &statusBarRect);
	this->heigth = statusBarRect.bottom - statusBarRect.top;

	//상태 표시줄의 구획 위치를 갱신한다. 
	const int parts = 5;
	int widths[parts] = { statusBarRect.right - 550, statusBarRect.right - 400, statusBarRect.right - 300, statusBarRect.right - 100 , -1 };
	this->notepad->statusBarCtrl.SetParts(parts, widths);

	//현재 위치를 읽는다. 
	lineOrder = this->notepad->notepannel->paper->GetCurrent();
	currentLine = this->notepad->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//현재 위치를 문자로 치환한다. 
	CString lineAndColumn;
	lineAndColumn.Format("Ln %d, Col %d", lineOrder + 1, charIndex + 1);
	this->currentLineAndColumn = (LPCSTR)lineAndColumn;

	//현재 배율을 읽는다.
	magnification = this->notepad->notepannel->zoomer->magnification;
	CString zoom;
	zoom.Format("%d", magnification);
	this->currentZoom = (LPCSTR)zoom;
	this->currentZoom = this->currentZoom + _T("%");

	//현재 바이트 코드
	//현재 인코딩

	//상태표시줄의 내용을 갱신한다. 
	this->notepad->statusBarCtrl.SetText(this->currentLineAndColumn.c_str(), 1, 0);
	this->notepad->statusBarCtrl.SetText(this->currentZoom.c_str(), 2, 0);
	this->notepad->statusBarCtrl.SetText(this->bytecode.c_str(), 3, 0);
	this->notepad->statusBarCtrl.SetText(this->incoding.c_str(), 4, 0);
}

/*
* 함수명칭:ShowStatusBar
* 기능:상태표시줄을 숨긴다
*/
void StatusBar::ShowStatusBar() {
	this->notepad->statusBarCtrl.ShowWindow(SW_SHOW);
}

/*
* 함수명칭:HideStatusBar
* 기능:상태표시줄을 표시한다. 
*/
void StatusBar::HideStatusBar() {
	this->notepad->statusBarCtrl.ShowWindow(SW_HIDE);
}