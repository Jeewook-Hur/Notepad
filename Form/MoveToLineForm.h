//MoveToLineForm.h
/**********************
* 파일명칭:MoveToLineForm.h
* 기능:줄 이동 창의 헤더
* 작성자:허지욱
* 작성일자:2023/2/6
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