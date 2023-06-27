//AboutNotepadForm.cpp
/*
* 파일명칭:AboutNotepadForm.cpp
* 기능:메모장 정보 창
* 작성자:허지욱
* 작성일자:2023/2/24
*/
#include "AboutNotepadForm.h"
#include "Notepannel.h"

BEGIN_MESSAGE_MAP(AboutNotepadForm, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_OK, OnOKButtonClicked)
END_MESSAGE_MAP()

/*
* 함수명칭:AboutNotepadForm
* 기능:생성자
*/
AboutNotepadForm::AboutNotepadForm(CWnd* parent, Notepannel* notepannel)
	:CDialog(AboutNotepadForm::IDD, parent), notepannel(notepannel) {
}

/*
* 함수명칭:OnInitDialog
* 기능:넣기창이 실행될때의 이벤트를 실행한다.
*/
BOOL AboutNotepadForm::OnInitDialog() {
	CString kor = "Windows 메모장\r\n버전 1.00\r\nCopyright(C) 허지욱(Hur Jeewook)\r\nAll right reserved";
	CString eng = "Windows Notepad\r\nver 1.00\r\nCopyright(C) Jeewook Hur\r\nAll right reserved";
	CString	warning = "경고: 이 컴퓨터 프로그램은 저작권법과 국제 협약이 보호를 받습니다. 이 프로그램의 전부 또는 일부를 무단으로 복제, 배포하는 행위는 민사 및 형사법에 의해 엄격히 규제되어 있으며, 기소 사유가 됩니다.";
	warning = warning + _T("\r\n\r\nWarning:This computer program is protected by copyright law and international treaties. ");
	warning = warning + _T("Unauthorized reproduction or distribution of this program, or any portion of it, may result in severe civiland criminal penalties, ");
	warning = warning + _T("and will be prosecuted to the maximum extent possible under the law.");

	GetDlgItem(IDC_STATIC_COPYRIGHTKOR)->SetWindowTextA(kor);
	GetDlgItem(IDC_STATIC_COPYRIGHTENG)->SetWindowTextA(eng);
	GetDlgItem(IDC_STATIC_WARNING)->SetWindowTextA(warning);

	return FALSE;
}

/*
* 함수명칭:OnClose
* 기능:넣기창을 닫는다.
*/
void AboutNotepadForm::OnClose() {
	this->EndDialog(0);
	this->notepannel->SetFocus();
}

/*
/*
* 함수명칭:OnOKButtonClicked
* 기능:버튼을 클릭했을때의 이벤트를 실행한다.
*/
void AboutNotepadForm::OnOKButtonClicked() {
	this->EndDialog(0);
	this->notepannel->SetFocus();
}