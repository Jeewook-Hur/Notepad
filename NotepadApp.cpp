//NotepadApp.cpp
/*
* ���ϸ�Ī:NotepadApp.cpp
* ���:�޸����� �����Ѵ�. 
* �ۼ���:������
* �ۼ�����:2022/7/18
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
	notepad->Create(NULL, "���� ���� - Windows �޸���");

	notepad->ShowWindow(m_nCmdShow);
	notepad->UpdateWindow();
	this->m_pMainWnd = notepad;

	//�̰� �Ⱦ��� ĳ���� �Ⱥ��δ�...
	notepad->notepannel->caret->ShowCaret();

	notepad->hasStarted = FALSE;

	return TRUE;
}

NotepadApp notepadApp;