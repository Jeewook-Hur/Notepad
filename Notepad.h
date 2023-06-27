//Notepad.h
/*
* ���ϸ�Ī:Notepad.h
* ���:�޸����� ���
* �ۼ���:������
* �ۼ�����:2022/7/18
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
	CMenu cMenu; // �׻� �ְ� �ϴ°� 
	CStatusBarCtrl statusBarCtrl;
	//CBitmap previousBitmap; //��¿� ����
	UINT nType; //ȭ�� ũ�� ���ſ� ���� �Լ�

	//�޴� �˾� ���� �Ӽ�
	BOOL menuPopuped;
	UINT nIndex; //�� �޴��� �˾� �޴� �ε��� 
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