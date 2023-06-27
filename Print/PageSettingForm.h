//PageSettingForm.h
/**********************
* 파일명칭:PageSettingForm.h
* 기능:페이지 설정 창의 헤더
* 작성자:허지욱
* 작성일자:2022/12/19
**********************/
#ifndef _PAGESETTINGFORM_H
#define _PAGESETTINGFORM_H
#include<afxwin.h>
#include "resource.h"

class Notepannel;
class PageSettingForm : public CDialog {
public:
	enum { IDD = IDD_PAGESETTINGFORM };
public:
	PageSettingForm(CWnd* parent = NULL, Notepannel* notepannel = NULL);
	virtual BOOL OnInitDialog();
private:
	Notepannel* notepannel;
protected:
	afx_msg void OnClose();
	afx_msg void OnCancelButtonClicked();
	afx_msg void OnOKButtonClicked();
	afx_msg void OnPreviewButtonClicked();
	afx_msg void OnPrintButtonClicked();
	DECLARE_MESSAGE_MAP()
};
#endif // !_PAGESETTINGFORM_H