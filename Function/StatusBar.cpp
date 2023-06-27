//StatusBar.cpp
/*
* ���ϸ�Ī:StatusBar.cpp
* ���:����ǥ���� Ŭ����
* �ۼ���:������
* �ۼ�����:2023/1/8
*/
#include "StatusBar.h"
#include "Notepad.h"
#include "Notepannel.h"

#include "Zoomer.h"
#include "Paper.h"
#include "Line.h"

/*
* �Լ���Ī:StatusBar
* ���:������
*/
StatusBar::StatusBar(Notepad* notepad) : notepad(notepad) {
	this->currentLineAndColumn = "Ln 1, Col 1";
	this->currentZoom = "100%";
	this->bytecode = "windowsCRLF";
	this->incoding = "ANSI";

	//����ǥ������ �����. 
	this->notepad->statusBarCtrl.Create(WS_CHILD | WS_VISIBLE | CCS_BOTTOM | SBARS_SIZEGRIP, CRect(0, 0, 0, 0), this->notepad, 100002);

	//����ǥ������ ũ�⸦ �����´�. 
	RECT statusBarRect;
	this->notepad->statusBarCtrl.GetRect(0, &statusBarRect);
	this->heigth = statusBarRect.bottom - statusBarRect.top;

	//���� ǥ������ ������. 
	const int parts = 5;
	int widths[parts] = { statusBarRect.right - 550, statusBarRect.right - 400, statusBarRect.right - 300, statusBarRect.right - 100 , -1 };
	this->notepad->statusBarCtrl.SetParts(parts, widths);

	//����ǥ������ ������ �����Ѵ�. 
	this->notepad->statusBarCtrl.SetText(this->currentLineAndColumn.c_str(), 1, 0);
	this->notepad->statusBarCtrl.SetText(this->currentZoom.c_str(), 2, 0);
	this->notepad->statusBarCtrl.SetText(this->bytecode.c_str(), 3, 0);
	this->notepad->statusBarCtrl.SetText(this->incoding.c_str(), 4, 0);
}

/*
* �Լ���Ī:~StatusBar
* ���:�Ҹ���
*/
StatusBar::~StatusBar() {
}

/*
* �Լ���Ī:UpdateStatusBar
* ���:����ǥ������ �ؽ�Ʈ�� �����Ѵ�.
*/
void StatusBar::UpdateStatusBar() {
	WINDOWINFO windowInfo{ 0, };
	CRect windowRect;
	CRect pannelRect;
	Glyph* currentLine;
	Long lineOrder;
	Long charIndex;
	int magnification;

	//Ŭ���̾�Ʈ�� ��ġ�� �д´�.
	this->notepad->GetWindowInfo(&windowInfo);
	windowRect = windowInfo.rcClient;
	//����ǥ������ ũ�⸦ Ŭ���̾�Ʈ�� �°� �����Ѵ�. 
	pannelRect = { 0,windowRect.bottom - this->heigth, windowRect.right - windowRect.left, this->heigth };
	this->notepad->statusBarCtrl.MoveWindow(&pannelRect);

	//����ǥ������ ũ�⸦ �����´�. 
	RECT statusBarRect;
	this->notepad->statusBarCtrl.GetRect(4, &statusBarRect);
	this->heigth = statusBarRect.bottom - statusBarRect.top;

	//���� ǥ������ ��ȹ ��ġ�� �����Ѵ�. 
	const int parts = 5;
	int widths[parts] = { statusBarRect.right - 550, statusBarRect.right - 400, statusBarRect.right - 300, statusBarRect.right - 100 , -1 };
	this->notepad->statusBarCtrl.SetParts(parts, widths);

	//���� ��ġ�� �д´�. 
	lineOrder = this->notepad->notepannel->paper->GetCurrent();
	currentLine = this->notepad->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//���� ��ġ�� ���ڷ� ġȯ�Ѵ�. 
	CString lineAndColumn;
	lineAndColumn.Format("Ln %d, Col %d", lineOrder + 1, charIndex + 1);
	this->currentLineAndColumn = (LPCSTR)lineAndColumn;

	//���� ������ �д´�.
	magnification = this->notepad->notepannel->zoomer->magnification;
	CString zoom;
	zoom.Format("%d", magnification);
	this->currentZoom = (LPCSTR)zoom;
	this->currentZoom = this->currentZoom + _T("%");

	//���� ����Ʈ �ڵ�
	//���� ���ڵ�

	//����ǥ������ ������ �����Ѵ�. 
	this->notepad->statusBarCtrl.SetText(this->currentLineAndColumn.c_str(), 1, 0);
	this->notepad->statusBarCtrl.SetText(this->currentZoom.c_str(), 2, 0);
	this->notepad->statusBarCtrl.SetText(this->bytecode.c_str(), 3, 0);
	this->notepad->statusBarCtrl.SetText(this->incoding.c_str(), 4, 0);
}

/*
* �Լ���Ī:ShowStatusBar
* ���:����ǥ������ �����
*/
void StatusBar::ShowStatusBar() {
	this->notepad->statusBarCtrl.ShowWindow(SW_SHOW);
}

/*
* �Լ���Ī:HideStatusBar
* ���:����ǥ������ ǥ���Ѵ�. 
*/
void StatusBar::HideStatusBar() {
	this->notepad->statusBarCtrl.ShowWindow(SW_HIDE);
}