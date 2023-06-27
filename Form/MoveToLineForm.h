//MoveToLineForm.h
/**********************
* ���ϸ�Ī:MoveToLineForm.h
* ���:�� �̵� â�� ���
* �ۼ���:������
* �ۼ�����:2023/2/6
**********************/
#ifndef _MOVETOLINEFORM_H
#define _MOVETOLINEFORM_H
#include<afxwin.h>
#include "resource.h"

class Notepannel;
class MoveToLineForm : public CDialog {
public:
	enum { IDD = IDD_MOVETOLINEFORM };
public:
	MoveToLineForm(CWnd* parent = NULL, Notepannel* notepannel = NULL);
	virtual BOOL OnInitDialog();
private:
	Notepannel* notepannel;
protected:
	afx_msg void OnClose();
	afx_msg void OnCancelButtonClicked();
	afx_msg void OnMoveButtonClicked();
	DECLARE_MESSAGE_MAP()
};
#endif // !_MOVETOLINEFORM_H