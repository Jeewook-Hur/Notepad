//AboutNotepadForm.h
/**********************
* ���ϸ�Ī:AboutNotepadForm.h
* ���:�޸��� ���� â�� ���
* �ۼ���:������
* �ۼ�����:2023/2/24
**********************/
#ifndef _ABOUTNOTEPADFORM_H
#define _ABOUTNOTEPADFORM_H
#include<afxwin.h>
#include "resource.h"

class Notepannel;
class AboutNotepadForm : public CDialog {
public:
	enum { IDD = IDD_ABOUTNOTEPAD };
public:
	AboutNotepadForm(CWnd* parent = NULL, Notepannel* notepannel = NULL);
	virtual BOOL OnInitDialog();
private:
	Notepannel* notepannel;
protected:
	afx_msg void OnClose();
	afx_msg void OnOKButtonClicked();
	DECLARE_MESSAGE_MAP()
};
#endif // !_ABOUTNOTEPADFORM_H