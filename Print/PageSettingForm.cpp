//PageSettingForm.cpp
/*
* 파일명칭:PageSettingForm.cpp
* 기능:페이지 설정 창
* 작성자:허지욱
* 작성일자:2022/12/19
*/
#include "PageSettingForm.h"
#include "Notepannel.h"
#include "PageSetting.h"
#include "Document.h"
#include "PreviewPage.h"
#include <afxdlgs.h>

BEGIN_MESSAGE_MAP(PageSettingForm, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnCancelButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnOKButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, OnPreviewButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnPrintButtonClicked)
END_MESSAGE_MAP()

/*
* 함수명칭:PageSettingForm
* 기능:생성자
*/
PageSettingForm::PageSettingForm(CWnd* parent, Notepannel* notepannel)
	:CDialog(PageSettingForm::IDD, parent), notepannel(notepannel) {
}

/*
* 함수명칭:OnInitDialog
* 기능:넣기창이 실행될때의 이벤트를 실행한다.
*/
BOOL PageSettingForm::OnInitDialog() {
	CDialog::OnInitDialog();
	string paperSize[1] = { "A4" };
	Long i = 0;
	while (i < sizeof(paperSize) / sizeof(paperSize[0])) {
		((CComboBox*)GetDlgItem(IDC_COMBO_PAPERSIZE))->AddString(paperSize[i].c_str());
		i++;
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_PAPERSIZE))->SetCurSel(0);

	((CButton*)GetDlgItem(IDC_RADIO_VERTICAL))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_HORIZONTAL))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_HORIZONTAL))->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_MARGINLEFT)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginLeft)).c_str());
	GetDlgItem(IDC_EDIT_MARGINRIGHT)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginRight)).c_str());
	GetDlgItem(IDC_EDIT_MARGINUP)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginTop)).c_str());
	GetDlgItem(IDC_EDIT_MARGINDOWN)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginBottom)).c_str());
	GetDlgItem(IDC_EDIT_HEADERLENGTH)->SetWindowTextA((to_string(this->notepannel->pageSetting->headerLength)).c_str());
	GetDlgItem(IDC_EDIT_FOOTERLENGTH)->SetWindowTextA((to_string(this->notepannel->pageSetting->footerLength)).c_str());
	GetDlgItem(IDC_EDIT_HEADERSTRING)->SetWindowTextA(this->notepannel->pageSetting->headerString.c_str());
	GetDlgItem(IDC_EDIT_FOOTERSTRING)->SetWindowTextA(this->notepannel->pageSetting->footerString.c_str());

	if (this->notepannel->pageSetting->headerString == "\0") {
		CString header = "";
		header.Format("%s.%s", this->notepannel->document->GetName().c_str(), this->notepannel->document->GetExtention().c_str());
		GetDlgItem(IDC_EDIT_HEADERSTRING)->SetWindowTextA(header);
	}
	return FALSE;
}

/*
* 함수명칭:OnClose
* 기능:넣기창을 닫는다.
*/
void PageSettingForm::OnClose() {
	this->EndDialog(0);
	this->notepannel->SetFocus();
}

/*
* 함수명칭:OnCancelButtonClicked
* 기능:버튼을 클릭했을때의 이벤트를 실행한다.
*/
void PageSettingForm::OnCancelButtonClicked() {
	this->EndDialog(0);
	this->notepannel->SetFocus();
}

/*
* 함수명칭:OnOKButtonClicked
* 기능:버튼을 클릭했을때의 이벤트를 실행한다.
*/
void PageSettingForm::OnOKButtonClicked() {
	CString marginLeft;
	CString marginRight;
	CString marginTop;
	CString marginBottom;
	CString headerLength;
	CString footerLength;
	CString headerString;
	CString footerString;
	int pageWidth = 210;
	int pageHeight = 297;

	GetDlgItem(IDC_EDIT_MARGINLEFT)->GetWindowTextA(marginLeft);
	GetDlgItem(IDC_EDIT_MARGINRIGHT)->GetWindowTextA(marginRight);
	GetDlgItem(IDC_EDIT_MARGINUP)->GetWindowTextA(marginTop);
	GetDlgItem(IDC_EDIT_MARGINDOWN)->GetWindowTextA(marginBottom);
	GetDlgItem(IDC_EDIT_HEADERLENGTH)->GetWindowTextA(headerLength);
	GetDlgItem(IDC_EDIT_FOOTERLENGTH)->GetWindowTextA(footerLength);
	GetDlgItem(IDC_EDIT_HEADERSTRING)->GetWindowTextA(headerString);
	GetDlgItem(IDC_EDIT_FOOTERSTRING)->GetWindowTextA(footerString);

	delete this->notepannel->pageSetting;
	this->notepannel->pageSetting = new PageSetting(this->notepannel, (LPCSTR)headerString, (LPCSTR)footerString, pageWidth, pageHeight,
		_ttoi(marginLeft), _ttoi(marginRight), _ttoi(marginTop), _ttoi(marginBottom), _ttoi(headerLength), _ttoi(footerLength));
	
	if (this->notepannel->pageSetting->hasFixed == false) {
		this->EndDialog(0);
		this->notepannel->SetFocus();
	}
	else if (this->notepannel->pageSetting->hasFixed == true) {
		MessageBoxA(_T("입력한 여백값이 용지의 크기를 초과하였기에 조정됩니다."));
		GetDlgItem(IDC_EDIT_MARGINLEFT)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginLeft)).c_str());
		GetDlgItem(IDC_EDIT_MARGINRIGHT)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginRight)).c_str());
		GetDlgItem(IDC_EDIT_MARGINUP)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginTop)).c_str());
		GetDlgItem(IDC_EDIT_MARGINDOWN)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginBottom)).c_str());
		GetDlgItem(IDC_EDIT_HEADERLENGTH)->SetWindowTextA((to_string(this->notepannel->pageSetting->headerLength)).c_str());
		GetDlgItem(IDC_EDIT_FOOTERLENGTH)->SetWindowTextA((to_string(this->notepannel->pageSetting->footerLength)).c_str());
	}

}

/*
* 함수명칭:OnPreviewButtonClicked
* 기능:버튼을 클릭했을때의 이벤트를 실행한다.
*/
void PageSettingForm::OnPreviewButtonClicked() {
	CString marginLeft;
	CString marginRight;
	CString marginTop;
	CString marginBottom;
	CString headerLength;
	CString footerLength;
	CString headerString;
	CString footerString;
	int pageWidth = 210;
	int pageHeight = 297;

	GetDlgItem(IDC_EDIT_MARGINLEFT)->GetWindowTextA(marginLeft);
	GetDlgItem(IDC_EDIT_MARGINRIGHT)->GetWindowTextA(marginRight);
	GetDlgItem(IDC_EDIT_MARGINUP)->GetWindowTextA(marginTop);
	GetDlgItem(IDC_EDIT_MARGINDOWN)->GetWindowTextA(marginBottom);
	GetDlgItem(IDC_EDIT_HEADERLENGTH)->GetWindowTextA(headerLength);
	GetDlgItem(IDC_EDIT_FOOTERLENGTH)->GetWindowTextA(footerLength);
	GetDlgItem(IDC_EDIT_HEADERSTRING)->GetWindowTextA(headerString);
	GetDlgItem(IDC_EDIT_FOOTERSTRING)->GetWindowTextA(footerString);

	delete this->notepannel->pageSetting;
	this->notepannel->pageSetting = new PageSetting(this->notepannel, (LPCSTR)headerString, (LPCSTR)footerString, pageWidth, pageHeight,
		_ttoi(marginLeft), _ttoi(marginRight), _ttoi(marginTop), _ttoi(marginBottom), _ttoi(headerLength), _ttoi(footerLength));
	
	
	
	
	if (this->notepannel->pageSetting->hasFixed == false) {
		PreviewPage* previewPage = new PreviewPage(this->notepannel);
		RECT pageSize = { 0, 0, 700, 950 };
		//미리보기 윈도우를 만든다
		previewPage->Create(NULL, "페이지 미리보기", WS_OVERLAPPEDWINDOW, pageSize, this);
		//미리보기 윈도우를 띄운다. 
		previewPage->ShowWindow(SW_SHOW);//MAXIMIZED);
		CRect windowSize = { 0,0, 630, 900 };
		previewPage->MoveWindow(&windowSize);
		previewPage->UpdateWindow();

	}
	else if (this->notepannel->pageSetting->hasFixed == true) {
		MessageBoxA(_T("입력한 여백값이 용지의 크기를 초과하였기에 조정됩니다."));
		GetDlgItem(IDC_EDIT_MARGINLEFT)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginLeft)).c_str());
		GetDlgItem(IDC_EDIT_MARGINRIGHT)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginRight)).c_str());
		GetDlgItem(IDC_EDIT_MARGINUP)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginTop)).c_str());
		GetDlgItem(IDC_EDIT_MARGINDOWN)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginBottom)).c_str());
		GetDlgItem(IDC_EDIT_HEADERLENGTH)->SetWindowTextA((to_string(this->notepannel->pageSetting->headerLength)).c_str());
		GetDlgItem(IDC_EDIT_FOOTERLENGTH)->SetWindowTextA((to_string(this->notepannel->pageSetting->footerLength)).c_str());
	}
	
}

/*
* 함수명칭:OnPrintButtonClicked
* 기능:인쇄 버튼을 눌렀을 때의 이벤트를 실행한다.
*/
void PageSettingForm::OnPrintButtonClicked() {
	CString marginLeft;
	CString marginRight;
	CString marginTop;
	CString marginBottom;
	CString headerLength;
	CString footerLength;
	CString headerString;
	CString footerString;
	int pageWidth = 210;
	int pageHeight = 297;

	GetDlgItem(IDC_EDIT_MARGINLEFT)->GetWindowTextA(marginLeft);
	GetDlgItem(IDC_EDIT_MARGINRIGHT)->GetWindowTextA(marginRight);
	GetDlgItem(IDC_EDIT_MARGINUP)->GetWindowTextA(marginTop);
	GetDlgItem(IDC_EDIT_MARGINDOWN)->GetWindowTextA(marginBottom);
	GetDlgItem(IDC_EDIT_HEADERLENGTH)->GetWindowTextA(headerLength);
	GetDlgItem(IDC_EDIT_FOOTERLENGTH)->GetWindowTextA(footerLength);
	GetDlgItem(IDC_EDIT_HEADERSTRING)->GetWindowTextA(headerString);
	GetDlgItem(IDC_EDIT_FOOTERSTRING)->GetWindowTextA(footerString);

	delete this->notepannel->pageSetting;
	this->notepannel->pageSetting = new PageSetting(this->notepannel, (LPCSTR)headerString, (LPCSTR)footerString, pageWidth, pageHeight,
		_ttoi(marginLeft), _ttoi(marginRight), _ttoi(marginTop), _ttoi(marginBottom), _ttoi(headerLength), _ttoi(footerLength));

	if (this->notepannel->pageSetting->hasFixed == false) {

		PreviewPage* previewPage;
		HDC hPrinter;
		RECT pageSize = { 0, 0, 700, 950 };
		//인쇄하기 일반대화상자를 만든다.
		CPrintDialogEx printDialogEx(PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS | PD_NOSELECTION | PD_NOCURRENTPAGE, this->notepannel);
		//인쇄하기 일반대화상자를 띄운다. 
		printDialogEx.DoModal();

		if (printDialogEx.m_pdex.dwResultAction == PD_RESULT_PRINT) { //인쇄하기를 눌렀을 경우
			//인쇄를 한다.
			//프린터의 디바이스 컨텍스트를 가져온다. 
			hPrinter = printDialogEx.CreatePrinterDC();

			previewPage = new PreviewPage(this->notepannel);

			//미리보기 페이지를 만든다. 
			previewPage->Create(NULL, "페이지 미리보기", WS_OVERLAPPEDWINDOW, pageSize, this->notepannel);
			//인쇄한다. 
			previewPage->Print(hPrinter);
			//인쇄를 마치면 미리보기 클래스를 할당해제한다. 
			//인쇄를 마치면 핸들을 제거한다.
			DeleteDC(hPrinter);
			this->EndDialog(0);
		}
		this->notepannel->SetFocus();
	}
	else if (this->notepannel->pageSetting->hasFixed == true) {
		MessageBoxA(_T("입력한 여백값이 용지의 크기를 초과하였기에 조정됩니다."));
		GetDlgItem(IDC_EDIT_MARGINLEFT)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginLeft)).c_str());
		GetDlgItem(IDC_EDIT_MARGINRIGHT)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginRight)).c_str());
		GetDlgItem(IDC_EDIT_MARGINUP)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginTop)).c_str());
		GetDlgItem(IDC_EDIT_MARGINDOWN)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginBottom)).c_str());
		GetDlgItem(IDC_EDIT_HEADERLENGTH)->SetWindowTextA((to_string(this->notepannel->pageSetting->headerLength)).c_str());
		GetDlgItem(IDC_EDIT_FOOTERLENGTH)->SetWindowTextA((to_string(this->notepannel->pageSetting->footerLength)).c_str());
	}
}