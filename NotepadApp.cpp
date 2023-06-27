//NotepadApp.cpp
/*
* 파일명칭:NotepadApp.cpp
* 기능:메모장을 실행한다. 
* 작성자:허지욱
* 작성일자:2022/7/18
*/
#include "NotepadApp.h"
#include "Notepad.h"
#include "Notepannel.h"
#include "Caret.h"
#include "resource.h"
#include<Windows.h>
#include<WinUser.h>

BOOL NotepadApp::InitInstance() {
	Notepad* notepad = new Notepad;
	notepad->Create(NULL, "제목 없음 - Windows 메모장");

	notepad->ShowWindow(m_nCmdShow);
	notepad->UpdateWindow();
	this->m_pMainWnd = notepad;

	//이거 안쓰면 캐럿이 안보인다...
	notepad->notepannel->caret->ShowCaret();

	notepad->hasStarted = FALSE;

	return TRUE;
}

NotepadApp notepadApp;