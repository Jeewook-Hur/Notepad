//Notepad.cpp
/*
* 파일명칭:Notepad.cpp
* 기능:메모장
* 작성자:허지욱
* 작성일자:2022/7/18
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
* 함수명칭:Notepad
* 기능:생성자
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
* 함수명칭:~Notepad
* 기능:소멸자
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
* 함수명칭:OnClose
* 기능:윈도우를 닫을때의 이벤트를 실행한다. 
*/
void Notepad::OnClose() {
	this->OnMenuItemChecked(IDM_FORMAT_CLOSE);
}

/*
* 함수명칭:OnCreate
* 기능:윈도우가 생성될때의 이벤트를 실행한다.
*/
int Notepad::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);
	WINDOWINFO windowInfo{ 0, };

	//메뉴를 출력한다. 
	cMenu.LoadMenuA(IDR_MENU);
	this->SetMenu(&cMenu);

	//아이콘을 출력한다.
	//HICON notepadIcon = LoadIconA(NULL, (LPCSTR)IDI_ICON_NOTEPAD);
	HICON notepadIcon = LoadIconA(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_NOTEPAD));
	this->SetIcon(notepadIcon, FALSE);


	//상태표시줄을 만든다.
	this->statusBar = new StatusBar(this);
	//메뉴에 상태표시줄을 체크한다. 
	this->cMenu.CheckMenuItem(IDM_FORMAT_STATUSBAR, MF_CHECKED);

	//클라이언트의 정보를 가져온다.
	this->GetWindowInfo(&windowInfo);
	this->notepannel = new Notepannel(this);
	CRect windowRect = windowInfo.rcClient;
	CRect pannelRect = { 0,0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top - this->statusBar->heigth };
	//패널을 만든다.
	this->notepannel->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, pannelRect, this, (UINT)100001);
	//패널을 출력한다.
	this->notepannel->ShowWindow(SW_SHOW);
	//패널을 갱신한다. 
	this->notepannel->UpdateWindow();
	//패널에 포커스를 한다
	this->notepannel->SetFocus();

	//상태표시줄을 업데이트 한다.
	this->statusBar->UpdateStatusBar();



	//DWORD error = GetLastError();
	return 0;
}

/*
* 함수명칭:OnSetFouct
* 기능:메모장에 포커스가 되었을 때의 이벤트를 실행한다. 
*/
void Notepad::OnSetFocus(CWnd* pOldWnd) {
	//패널에 포커스를 준다.
	this->notepannel->SetFocus();
	//패널의 포커스 메시지를 보낸다.
	this->notepannel->SendMessageA(WM_SETFOCUS, 0, 0);

	this->notepannel->ShowCaret();
}


/*
* 함수명칭:OnMenuItemChecked
* 기능: 입력받은 메뉴에 맞는 명령을 생성하여 실행한다.
*/
void Notepad::OnMenuItemChecked(UINT uID) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	UINT lineWrapState = -1;
	UINT statusBarState = -1;

	//입력받은 메뉴에 맞는 커멘드를 만든다.
	command = commandCreator.Create(uID);
	//개행 여부를 알아본다.
	lineWrapState = this->cMenu.GetMenuState(IDM_FORMAT_LINEWRAP, MF_BYCOMMAND);
	//상태표시줄 표시 여부를 알아본다.
	statusBarState = this->cMenu.GetMenuState(IDM_FORMAT_STATUSBAR, MF_BYCOMMAND);

	if (command != NULL && uID != IDM_FORMAT_LINEWRAP && uID != IDM_FORMAT_REDO && uID != IDM_FORMAT_CUT && uID != IDM_FORMAT_PASTE && uID != IDM_FORMAT_STATUSBAR) { //커멘트가 반환되었을경우
		command->Execute();
		delete command;
	}
	else if (command != NULL && uID == IDM_FORMAT_REDO) {
		command->UnExecute();
		delete command;
	}
	else if (command != NULL && uID == IDM_FORMAT_LINEWRAP) { //자동 줄 바꿈 메뉴를 체크했을 경우
		if (lineWrapState == MF_UNCHECKED) {
			this->notepannel->isCalledFromMenu = TRUE;
			command->Execute();
			//개행에 넣기
			this->cMenu.CheckMenuItem(IDM_FORMAT_LINEWRAP, MF_CHECKED);
		}
		else if (lineWrapState == MF_CHECKED) {
			this->notepannel->isCalledFromMenu = TRUE;
			command->UnExecute();
			//개행취소에 넣기
			this->cMenu.CheckMenuItem(IDM_FORMAT_LINEWRAP, MF_UNCHECKED);
		}
		delete command;
	}
	else if (command != NULL && (uID == IDM_FORMAT_CUT || uID == IDM_FORMAT_PASTE)) { //나중에 PASTE도 추가한다. 
		command->Execute();
		this->notepannel->macroCommand->Add(command);
	}
	else if (command != NULL && uID == IDM_FORMAT_STATUSBAR) { //상태표시줄 표시 메뉴를 체크했을 경우
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
* 함수명칭:OnInitMenu
* 기능:메뉴창을 선택했을 때의 이벤트를 실행한다.
*/
void Notepad::OnInitMenu(CMenu* pMenu) {
	this->OnInitMenuPopup(pMenu, 1, TRUE);
}

/*
* 함수명칭:OnInitMenuPopup
* 기능:메뉴창에서 팝업이 되었을 때의 이벤트를 실행한다.
*/
void Notepad::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) {
	BOOL clipboardThing = FALSE;
	Long charNumber = this->notepannel->paper->GetCharNumber();
	UINT lineWrapState = -1;

	this->menuPopuped = TRUE;
	this->nIndex = nIndex;

	lineWrapState = this->cMenu.GetMenuState(IDM_FORMAT_LINEWRAP, MF_BYCOMMAND);

	if (this->notepannel->select->currentLineOrder == this->notepannel->select->previousLineOrder && this->notepannel->select->currentXIndex == this->notepannel->select->previousXIndex) { //문서가 선택되어있지 않으면
		//잘라내기 항목을 비활성화 한다.
		this->cMenu.EnableMenuItem(IDM_FORMAT_CUT, MF_DISABLED | MF_GRAYED);
		//복사 항목을 비활성화 한다
		this->cMenu.EnableMenuItem(IDM_FORMAT_COPY, MF_DISABLED | MF_GRAYED);
		//삭제 항목을 비활성화 한다. 
		this->cMenu.EnableMenuItem(IDM_FORMAT_DELETE, MF_DISABLED | MF_GRAYED);
	}
	else { //문서가 선택되어있으면
		//잘라내기 항목을 활성화 한다.
		this->cMenu.EnableMenuItem(IDM_FORMAT_CUT, MF_ENABLED);
		//복사 항목을 활성화 한다
		this->cMenu.EnableMenuItem(IDM_FORMAT_COPY, MF_ENABLED);
		//삭제 항목을 활성화 한다. 
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

	if (charNumber > 0) { // 문서에 내용이 있으면
		this->cMenu.EnableMenuItem(IDM_FORMAT_FIND, MF_ENABLED);
		this->cMenu.EnableMenuItem(IDM_FORMAT_FINDNEXT, MF_ENABLED);
		this->cMenu.EnableMenuItem(IDM_FORMAT_FINDPREVIOUS, MF_ENABLED);

	}
	else {
		this->cMenu.EnableMenuItem(IDM_FORMAT_FIND, MF_DISABLED | MF_GRAYED);
		this->cMenu.EnableMenuItem(IDM_FORMAT_FINDNEXT, MF_DISABLED | MF_GRAYED);
		this->cMenu.EnableMenuItem(IDM_FORMAT_FINDPREVIOUS, MF_DISABLED | MF_GRAYED);
	}

	if (lineWrapState == MF_UNCHECKED) { //자동 줄 바꿈 메뉴를 체크했을 경우
		this->cMenu.EnableMenuItem(IDM_FORMAT_MOVETO, MF_ENABLED);
	}
	else if (lineWrapState == MF_CHECKED) {
		this->cMenu.EnableMenuItem(IDM_FORMAT_MOVETO, MF_DISABLED | MF_GRAYED);
	}
}

/*
* 함수명칭:OnUnInitMenuPopup
* 기능:메뉴에서 팝업이 닫혔을때의 이벤트를 실행한다.
*/
void Notepad::OnUnInitMenuPopup(CMenu* pPopupMenu, UINT nFlags) {
	this->menuPopuped = FALSE;
}


/*
* 함수명칭:OnMenuChar
* 기능:메뉴를 선택할때 누른 단축키에 맞는 메뉴를 실행한다. 
*/
LRESULT Notepad::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) {
	
	UINT uID = -1;

	//각 단축키에 맞는 팝업을 생성한다. 

	
	//각 단축키에 맞는 커멘트를 생성한다. 
	if (this->nIndex == 0 && (nChar == 'n' || nChar == 'N')) { //대소문자 다 되게 하자....
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
* 함수명칭:OnSize
* 기능:윈도우 크기가 최대화될때, 최대화에서 일반화 될때의 이벤트를 처리한다.
*/
void Notepad::OnSize(UINT nType, int cx, int cy) {
	this->nType = nType;
	if (this->notepannel != 0) {
		this->notepannel->SendMessageA(WM_SIZE, 0, 0);
	}
}

/*
* 함수명칭:OnSizing
* 기능:사용자가 윈도우 크기를 조절할때의 이벤트를 실행한다.
*/
void Notepad::OnSizing(UINT nSide, LPRECT lpRect) {
	if (this->notepannel != 0) {
		this->notepannel->SendMessageA(WM_SIZING, 0, 0);
	}
}

/*
* 함수명칭:OnHelp
* 기능:
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