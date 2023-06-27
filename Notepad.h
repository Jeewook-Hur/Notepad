//Notepad.h
/*
* 파일명칭:Notepad.h
* 기능:메모장의 헤더
* 작성자:허지욱
* 작성일자:2022/7/18
*/
#ifndef _NOTEPAD_H
#define _NOTEPAD_H
#include<afxwin.h>
#include<afxcmn.h> // CMenu, CStatusBarCtrl
//#include<afxext.h> // CStatusBar

class StatusBar;
class Notepannel;
class Notepad : public CFrameWnd {
public:
	Notepad();
	~Notepad();
	CMenu cMenu; // 항상 있게 하는거 
	CStatusBarCtrl statusBarCtrl;
	//CBitmap previousBitmap; //출력용 예비
	UINT nType; //화면 크기 갱신에 대한 함수

	//메뉴 팝업 관련 속성
	BOOL menuPopuped;
	UINT nIndex; //주 메뉴의 팝업 메뉴 인덱스 
	BOOL bSysMenu;

	BOOL hasStarted;

	Notepannel* notepannel;
	StatusBar* statusBar;
protected:
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnMenuItemChecked(UINT uID);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnUnInitMenuPopup(CMenu* pPopupMenu, UINT nFlags);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT nSide, LPRECT lpRect);

	afx_msg void OnHelp();

	DECLARE_MESSAGE_MAP()
};

#endif // !_NOTEPAD_H