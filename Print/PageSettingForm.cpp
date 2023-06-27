//PageSettingForm.cpp
/*
* ���ϸ�Ī:PageSettingForm.cpp
* ���:������ ���� â
* �ۼ���:������
* �ۼ�����:2022/12/19
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
* �Լ���Ī:PageSettingForm
* ���:������
*/
PageSettingForm::PageSettingForm(CWnd* parent, Notepannel* notepannel)
	:CDialog(PageSettingForm::IDD, parent), notepannel(notepannel) {
}

/*
* �Լ���Ī:OnInitDialog
* ���:�ֱ�â�� ����ɶ��� �̺�Ʈ�� �����Ѵ�.
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
* �Լ���Ī:OnClose
* ���:�ֱ�â�� �ݴ´�.
*/
void PageSettingForm::OnClose() {
	this->EndDialog(0);
	this->notepannel->SetFocus();
}

/*
* �Լ���Ī:OnCancelButtonClicked
* ���:��ư�� Ŭ���������� �̺�Ʈ�� �����Ѵ�.
*/
void PageSettingForm::OnCancelButtonClicked() {
	this->EndDialog(0);
	this->notepannel->SetFocus();
}

/*
* �Լ���Ī:OnOKButtonClicked
* ���:��ư�� Ŭ���������� �̺�Ʈ�� �����Ѵ�.
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
		MessageBoxA(_T("�Է��� ���鰪�� ������ ũ�⸦ �ʰ��Ͽ��⿡ �����˴ϴ�."));
		GetDlgItem(IDC_EDIT_MARGINLEFT)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginLeft)).c_str());
		GetDlgItem(IDC_EDIT_MARGINRIGHT)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginRight)).c_str());
		GetDlgItem(IDC_EDIT_MARGINUP)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginTop)).c_str());
		GetDlgItem(IDC_EDIT_MARGINDOWN)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginBottom)).c_str());
		GetDlgItem(IDC_EDIT_HEADERLENGTH)->SetWindowTextA((to_string(this->notepannel->pageSetting->headerLength)).c_str());
		GetDlgItem(IDC_EDIT_FOOTERLENGTH)->SetWindowTextA((to_string(this->notepannel->pageSetting->footerLength)).c_str());
	}

}

/*
* �Լ���Ī:OnPreviewButtonClicked
* ���:��ư�� Ŭ���������� �̺�Ʈ�� �����Ѵ�.
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
		//�̸����� �����츦 �����
		previewPage->Create(NULL, "������ �̸�����", WS_OVERLAPPEDWINDOW, pageSize, this);
		//�̸����� �����츦 ����. 
		previewPage->ShowWindow(SW_SHOW);//MAXIMIZED);
		CRect windowSize = { 0,0, 630, 900 };
		previewPage->MoveWindow(&windowSize);
		previewPage->UpdateWindow();

	}
	else if (this->notepannel->pageSetting->hasFixed == true) {
		MessageBoxA(_T("�Է��� ���鰪�� ������ ũ�⸦ �ʰ��Ͽ��⿡ �����˴ϴ�."));
		GetDlgItem(IDC_EDIT_MARGINLEFT)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginLeft)).c_str());
		GetDlgItem(IDC_EDIT_MARGINRIGHT)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginRight)).c_str());
		GetDlgItem(IDC_EDIT_MARGINUP)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginTop)).c_str());
		GetDlgItem(IDC_EDIT_MARGINDOWN)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginBottom)).c_str());
		GetDlgItem(IDC_EDIT_HEADERLENGTH)->SetWindowTextA((to_string(this->notepannel->pageSetting->headerLength)).c_str());
		GetDlgItem(IDC_EDIT_FOOTERLENGTH)->SetWindowTextA((to_string(this->notepannel->pageSetting->footerLength)).c_str());
	}
	
}

/*
* �Լ���Ī:OnPrintButtonClicked
* ���:�μ� ��ư�� ������ ���� �̺�Ʈ�� �����Ѵ�.
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
		//�μ��ϱ� �Ϲݴ�ȭ���ڸ� �����.
		CPrintDialogEx printDialogEx(PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS | PD_NOSELECTION | PD_NOCURRENTPAGE, this->notepannel);
		//�μ��ϱ� �Ϲݴ�ȭ���ڸ� ����. 
		printDialogEx.DoModal();

		if (printDialogEx.m_pdex.dwResultAction == PD_RESULT_PRINT) { //�μ��ϱ⸦ ������ ���
			//�μ⸦ �Ѵ�.
			//�������� ����̽� ���ؽ�Ʈ�� �����´�. 
			hPrinter = printDialogEx.CreatePrinterDC();

			previewPage = new PreviewPage(this->notepannel);

			//�̸����� �������� �����. 
			previewPage->Create(NULL, "������ �̸�����", WS_OVERLAPPEDWINDOW, pageSize, this->notepannel);
			//�μ��Ѵ�. 
			previewPage->Print(hPrinter);
			//�μ⸦ ��ġ�� �̸����� Ŭ������ �Ҵ������Ѵ�. 
			//�μ⸦ ��ġ�� �ڵ��� �����Ѵ�.
			DeleteDC(hPrinter);
			this->EndDialog(0);
		}
		this->notepannel->SetFocus();
	}
	else if (this->notepannel->pageSetting->hasFixed == true) {
		MessageBoxA(_T("�Է��� ���鰪�� ������ ũ�⸦ �ʰ��Ͽ��⿡ �����˴ϴ�."));
		GetDlgItem(IDC_EDIT_MARGINLEFT)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginLeft)).c_str());
		GetDlgItem(IDC_EDIT_MARGINRIGHT)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginRight)).c_str());
		GetDlgItem(IDC_EDIT_MARGINUP)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginTop)).c_str());
		GetDlgItem(IDC_EDIT_MARGINDOWN)->SetWindowTextA((to_string(this->notepannel->pageSetting->marginBottom)).c_str());
		GetDlgItem(IDC_EDIT_HEADERLENGTH)->SetWindowTextA((to_string(this->notepannel->pageSetting->headerLength)).c_str());
		GetDlgItem(IDC_EDIT_FOOTERLENGTH)->SetWindowTextA((to_string(this->notepannel->pageSetting->footerLength)).c_str());
	}
}