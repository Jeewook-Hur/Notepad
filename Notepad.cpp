//Notepad.cpp
/*
* ���ϸ�Ī:Notepad.cpp
* ���:�޸���
* �ۼ���:������
* �ۼ�����:2022/7/18
*/
#include "Notepad.h"
#include "Notepannel.h"
#include "StatusBar.h"
#include "resource.h"
#include "Command.h"
#include "CommandCreator.h"
#include "ClientMatrix.h"
#include "Select.h"
#include "MacroCommand.h"
#include "Clipboard.h"
#include "Paper.h"
#include<afxcmn.h> // CMenu, CStatusBarCtrl
#include <string>
using namespace std;

#include<shellapi.h>


BEGIN_MESSAGE_MAP(Notepad, CFrameWnd)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(IDM_FORMAT_FONT, IDM_FORMAT_PREVIEW, OnMenuItemChecked)
	ON_WM_INITMENU()
	ON_WM_INITMENUPOPUP()
	ON_WM_MENUCHAR()

	ON_WM_SIZE()
	ON_WM_SIZING()

	ON_COMMAND(ID_HELP, OnHelp)

END_MESSAGE_MAP()

/*
* �Լ���Ī:Notepad
* ���:������
*/
Notepad::Notepad() {
	this->notepannel = NULL;
	this->statusBar = NULL;
	this->nType = 0;
	this->menuPopuped = FALSE;
	this->nIndex = 999;
	this->bSysMenu = FALSE;
	this->hasStarted = TRUE;
}

/*
* �Լ���Ī:~Notepad
* ���:�Ҹ���
*/
Notepad::~Notepad() {
	if (this->notepannel != NULL) {
		delete this->notepannel;
	}
	if (this->statusBar != NULL) {
		delete this->statusBar;
	}
	CWnd::DestroyWindow();
}

/*
* �Լ���Ī:OnClose
* ���:�����츦 �������� �̺�Ʈ�� �����Ѵ�. 
*/
void Notepad::OnClose() {
	this->OnMenuItemChecked(IDM_FORMAT_CLOSE);
}

/*
* �Լ���Ī:OnCreate
* ���:�����찡 �����ɶ��� �̺�Ʈ�� �����Ѵ�.
*/
int Notepad::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);
	WINDOWINFO windowInfo{ 0, };

	//�޴��� ����Ѵ�. 
	cMenu.LoadMenuA(IDR_MENU);
	this->SetMenu(&cMenu);

	//�������� ����Ѵ�.
	//HICON notepadIcon = LoadIconA(NULL, (LPCSTR)IDI_ICON_NOTEPAD);
	HICON notepadIcon = LoadIconA(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_NOTEPAD));
	this->SetIcon(notepadIcon, FALSE);


	//����ǥ������ �����.
	this->statusBar = new StatusBar(this);
	//�޴��� ����ǥ������ üũ�Ѵ�. 
	this->cMenu.CheckMenuItem(IDM_FORMAT_STATUSBAR, MF_CHECKED);

	//Ŭ���̾�Ʈ�� ������ �����´�.
	this->GetWindowInfo(&windowInfo);
	this->notepannel = new Notepannel(this);
	CRect windowRect = windowInfo.rcClient;
	CRect pannelRect = { 0,0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top - this->statusBar->heigth };
	//�г��� �����.
	this->notepannel->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, pannelRect, this, (UINT)100001);
	//�г��� ����Ѵ�.
	this->notepannel->ShowWindow(SW_SHOW);
	//�г��� �����Ѵ�. 
	this->notepannel->UpdateWindow();
	//�гο� ��Ŀ���� �Ѵ�
	this->notepannel->SetFocus();

	//����ǥ������ ������Ʈ �Ѵ�.
	this->statusBar->UpdateStatusBar();



	//DWORD error = GetLastError();
	return 0;
}

/*
* �Լ���Ī:OnSetFouct
* ���:�޸��忡 ��Ŀ���� �Ǿ��� ���� �̺�Ʈ�� �����Ѵ�. 
*/
void Notepad::OnSetFocus(CWnd* pOldWnd) {
	//�гο� ��Ŀ���� �ش�.
	this->notepannel->SetFocus();
	//�г��� ��Ŀ�� �޽����� ������.
	this->notepannel->SendMessageA(WM_SETFOCUS, 0, 0);

	this->notepannel->ShowCaret();
}


/*
* �Լ���Ī:OnMenuItemChecked
* ���: �Է¹��� �޴��� �´� ����� �����Ͽ� �����Ѵ�.
*/
void Notepad::OnMenuItemChecked(UINT uID) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	UINT lineWrapState = -1;
	UINT statusBarState = -1;

	//�Է¹��� �޴��� �´� Ŀ��带 �����.
	command = commandCreator.Create(uID);
	//���� ���θ� �˾ƺ���.
	lineWrapState = this->cMenu.GetMenuState(IDM_FORMAT_LINEWRAP, MF_BYCOMMAND);
	//����ǥ���� ǥ�� ���θ� �˾ƺ���.
	statusBarState = this->cMenu.GetMenuState(IDM_FORMAT_STATUSBAR, MF_BYCOMMAND);

	if (command != NULL && uID != IDM_FORMAT_LINEWRAP && uID != IDM_FORMAT_REDO && uID != IDM_FORMAT_CUT && uID != IDM_FORMAT_PASTE && uID != IDM_FORMAT_STATUSBAR) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
		command->Execute();
		delete command;
	}
	else if (command != NULL && uID == IDM_FORMAT_REDO) {
		command->UnExecute();
		delete command;
	}
	else if (command != NULL && uID == IDM_FORMAT_LINEWRAP) { //�ڵ� �� �ٲ� �޴��� üũ���� ���
		if (lineWrapState == MF_UNCHECKED) {
			this->notepannel->isCalledFromMenu = TRUE;
			command->Execute();
			//���࿡ �ֱ�
			this->cMenu.CheckMenuItem(IDM_FORMAT_LINEWRAP, MF_CHECKED);
		}
		else if (lineWrapState == MF_CHECKED) {
			this->notepannel->isCalledFromMenu = TRUE;
			command->UnExecute();
			//������ҿ� �ֱ�
			this->cMenu.CheckMenuItem(IDM_FORMAT_LINEWRAP, MF_UNCHECKED);
		}
		delete command;
	}
	else if (command != NULL && (uID == IDM_FORMAT_CUT || uID == IDM_FORMAT_PASTE)) { //���߿� PASTE�� �߰��Ѵ�. 
		command->Execute();
		this->notepannel->macroCommand->Add(command);
	}
	else if (command != NULL && uID == IDM_FORMAT_STATUSBAR) { //����ǥ���� ǥ�� �޴��� üũ���� ���
		if (statusBarState == MF_UNCHECKED) {
			//this->notepannel->isCalledFromMenu = TRUE;
			command->Execute();
			this->cMenu.CheckMenuItem(IDM_FORMAT_STATUSBAR, MF_CHECKED);
		}
		else if (statusBarState == MF_CHECKED) {
			//this->notepannel->isCalledFromMenu = TRUE;
			command->UnExecute();
			this->cMenu.CheckMenuItem(IDM_FORMAT_STATUSBAR, MF_UNCHECKED);
		}
		delete command;
	}
}

/*
* �Լ���Ī:OnInitMenu
* ���:�޴�â�� �������� ���� �̺�Ʈ�� �����Ѵ�.
*/
void Notepad::OnInitMenu(CMenu* pMenu) {
	this->OnInitMenuPopup(pMenu, 1, TRUE);
}

/*
* �Լ���Ī:OnInitMenuPopup
* ���:�޴�â���� �˾��� �Ǿ��� ���� �̺�Ʈ�� �����Ѵ�.
*/
void Notepad::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) {
	BOOL clipboardThing = FALSE;
	Long charNumber = this->notepannel->paper->GetCharNumber();
	UINT lineWrapState = -1;

	this->menuPopuped = TRUE;
	this->nIndex = nIndex;

	lineWrapState = this->cMenu.GetMenuState(IDM_FORMAT_LINEWRAP, MF_BYCOMMAND);

	if (this->notepannel->select->currentLineOrder == this->notepannel->select->previousLineOrder && this->notepannel->select->currentXIndex == this->notepannel->select->previousXIndex) { //������ ���õǾ����� ������
		//�߶󳻱� �׸��� ��Ȱ��ȭ �Ѵ�.
		this->cMenu.EnableMenuItem(IDM_FORMAT_CUT, MF_DISABLED | MF_GRAYED);
		//���� �׸��� ��Ȱ��ȭ �Ѵ�
		this->cMenu.EnableMenuItem(IDM_FORMAT_COPY, MF_DISABLED | MF_GRAYED);
		//���� �׸��� ��Ȱ��ȭ �Ѵ�. 
		this->cMenu.EnableMenuItem(IDM_FORMAT_DELETE, MF_DISABLED | MF_GRAYED);
	}
	else { //������ ���õǾ�������
		//�߶󳻱� �׸��� Ȱ��ȭ �Ѵ�.
		this->cMenu.EnableMenuItem(IDM_FORMAT_CUT, MF_ENABLED);
		//���� �׸��� Ȱ��ȭ �Ѵ�
		this->cMenu.EnableMenuItem(IDM_FORMAT_COPY, MF_ENABLED);
		//���� �׸��� Ȱ��ȭ �Ѵ�. 
		this->cMenu.EnableMenuItem(IDM_FORMAT_DELETE, MF_ENABLED);
	}

	clipboardThing = this->notepannel->clipboard->Check();
	if (clipboardThing == TRUE) {
		this->cMenu.EnableMenuItem(IDM_FORMAT_PASTE, MF_ENABLED);
	}
	else if (clipboardThing == FALSE) {
		this->cMenu.EnableMenuItem(IDM_FORMAT_PASTE, MF_DISABLED | MF_GRAYED);
	}

	if (this->notepannel->macroCommand->ToUndo() == true) {
		this->cMenu.EnableMenuItem(IDM_FORMAT_UNDO, MF_ENABLED);
	}
	else {
		this->cMenu.EnableMenuItem(IDM_FORMAT_UNDO, MF_DISABLED | MF_GRAYED);
	}

	if (this->notepannel->macroCommand->ToRedo() == true) {
		this->cMenu.EnableMenuItem(IDM_FORMAT_REDO, MF_ENABLED);
	}
	else {
		this->cMenu.EnableMenuItem(IDM_FORMAT_REDO, MF_DISABLED | MF_GRAYED);
	}

	if (charNumber > 0) { // ������ ������ ������
		this->cMenu.EnableMenuItem(IDM_FORMAT_FIND, MF_ENABLED);
		this->cMenu.EnableMenuItem(IDM_FORMAT_FINDNEXT, MF_ENABLED);
		this->cMenu.EnableMenuItem(IDM_FORMAT_FINDPREVIOUS, MF_ENABLED);

	}
	else {
		this->cMenu.EnableMenuItem(IDM_FORMAT_FIND, MF_DISABLED | MF_GRAYED);
		this->cMenu.EnableMenuItem(IDM_FORMAT_FINDNEXT, MF_DISABLED | MF_GRAYED);
		this->cMenu.EnableMenuItem(IDM_FORMAT_FINDPREVIOUS, MF_DISABLED | MF_GRAYED);
	}

	if (lineWrapState == MF_UNCHECKED) { //�ڵ� �� �ٲ� �޴��� üũ���� ���
		this->cMenu.EnableMenuItem(IDM_FORMAT_MOVETO, MF_ENABLED);
	}
	else if (lineWrapState == MF_CHECKED) {
		this->cMenu.EnableMenuItem(IDM_FORMAT_MOVETO, MF_DISABLED | MF_GRAYED);
	}
}

/*
* �Լ���Ī:OnUnInitMenuPopup
* ���:�޴����� �˾��� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void Notepad::OnUnInitMenuPopup(CMenu* pPopupMenu, UINT nFlags) {
	this->menuPopuped = FALSE;
}


/*
* �Լ���Ī:OnMenuChar
* ���:�޴��� �����Ҷ� ���� ����Ű�� �´� �޴��� �����Ѵ�. 
*/
LRESULT Notepad::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) {
	
	UINT uID = -1;

	//�� ����Ű�� �´� �˾��� �����Ѵ�. 

	
	//�� ����Ű�� �´� Ŀ��Ʈ�� �����Ѵ�. 
	if (this->nIndex == 0 && (nChar == 'n' || nChar == 'N')) { //��ҹ��� �� �ǰ� ����....
		uID = IDM_FORMAT_NEW;
	}
	else if (this->nIndex == 0 && (nChar == 'o' || nChar == 'O')) {
		uID = IDM_FORMAT_LOAD;
	}
	else if (this->nIndex == 0 && (nChar == 's' || nChar == 'S')) {
		uID = IDM_FORMAT_SAVE;
	}
	else if (this->nIndex == 0 && (nChar == 'a' || nChar == 'A')) {
		uID = IDM_FORMAT_SAVEAS;
	}
	else if (this->nIndex == 0 && (nChar == 'u' || nChar == 'U')) {
		uID = IDM_FORMAT_PAGESETTING;
	}
	else if (this->nIndex == 0 && (nChar == 'p' || nChar == 'P')) {
		uID = IDM_FORMAT_PRINT;
	}
	
	else if (this->nIndex == 1 && (nChar == 'u' || nChar == 'U')) {
		uID = IDM_FORMAT_UNDO;
	}
	else if (this->nIndex == 1 && (nChar == 'c' || nChar == 'C')) {
		uID = IDM_FORMAT_CUT;
	}
	else if (this->nIndex == 1 && (nChar == 't' || nChar == 'T')) {
		uID = IDM_FORMAT_COPY;
	}
	else if (this->nIndex == 1 && (nChar == 'p' || nChar == 'P')) {
		uID = IDM_FORMAT_PASTE;
	}
	else if (this->nIndex == 1 && (nChar == 'l' || nChar == 'L')) {
		uID = IDM_FORMAT_DELETE;
	}
	else if (this->nIndex == 1 && (nChar == 'f' || nChar == 'F')) {
		uID = IDM_FORMAT_FIND;
	}
	else if (this->nIndex == 1 && (nChar == 'n' || nChar == 'N')) {
		uID = IDM_FORMAT_FINDNEXT;
	}
	else if (this->nIndex == 1 && (nChar == 'v' || nChar == 'V')) {
		uID = IDM_FORMAT_FINDPREVIOUS;
	}
	else if (this->nIndex == 1 && (nChar == 'r' || nChar == 'R')) {
		uID = IDM_FORMAT_REPLACE;
	}
	else if (this->nIndex == 1 && (nChar == 'g' || nChar == 'G')) {
		uID = IDM_FORMAT_MOVETO;
	}
	else if (this->nIndex == 1 && (nChar == 'a' || nChar == 'A')) {
		uID = IDM_FORMAT_REPLACE;
	}
	else if (this->nIndex == 1 && (nChar == 'd' || nChar == 'D')) {
		uID = IDM_FORMAT_DATE;
	}

	else if (this->nIndex == 2 && (nChar == 'w' || nChar == 'W')) {
		uID = IDM_FORMAT_LINEWRAP;
	}
	else if (this->nIndex == 2 && (nChar == 'f' || nChar == 'F')) {
		uID = IDM_FORMAT_FONT;
	}

	else if (this->nIndex == 3 && (nChar == 's' || nChar == 'S')) {
		uID = IDM_FORMAT_STATUSBAR;
	}

	else if (this->nIndex == 4 && (nChar == 'h' || nChar == 'H')) {
		uID = IDM_FORMAT_VIEWHELP;
	}

	//this->SendMessageA(WM_CANCELMODE);

	if (uID != -1) {
		this->OnMenuItemChecked(uID);
	}

	return 1;
}


/*
* �Լ���Ī:OnSize
* ���:������ ũ�Ⱑ �ִ�ȭ�ɶ�, �ִ�ȭ���� �Ϲ�ȭ �ɶ��� �̺�Ʈ�� ó���Ѵ�.
*/
void Notepad::OnSize(UINT nType, int cx, int cy) {
	this->nType = nType;
	if (this->notepannel != 0) {
		this->notepannel->SendMessageA(WM_SIZE, 0, 0);
	}
}

/*
* �Լ���Ī:OnSizing
* ���:����ڰ� ������ ũ�⸦ �����Ҷ��� �̺�Ʈ�� �����Ѵ�.
*/
void Notepad::OnSizing(UINT nSide, LPRECT lpRect) {
	if (this->notepannel != 0) {
		this->notepannel->SendMessageA(WM_SIZING, 0, 0);
	}
}

/*
* �Լ���Ī:OnHelp
* ���:
*/
void Notepad::OnHelp() {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;

	command = commandCreator.Create(IDM_FORMAT_VIEWHELP);
	if (command != 0) {
		command->Execute();
		delete command;
	}
}