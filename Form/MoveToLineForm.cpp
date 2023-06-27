//MoveToLineForm.cpp
/*
* ���ϸ�Ī:MoveToLineForm.cpp
* ���:�� �̵� â â
* �ۼ���:������
* �ۼ�����:2023/2/6
*/
#include "MoveToLineForm.h"
#include "Notepannel.h"

#include "Caret.h"
#include "Select.h"

#include "Paper.h"
#include "Line.h"


BEGIN_MESSAGE_MAP(MoveToLineForm, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnCancelButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_MOVE, OnMoveButtonClicked)
END_MESSAGE_MAP()

/*
* �Լ���Ī:MoveToLineForm
* ���:������
*/
MoveToLineForm::MoveToLineForm(CWnd* parent, Notepannel* notepannel)
	:CDialog(MoveToLineForm::IDD, parent), notepannel(notepannel) {
}

/*
* �Լ���Ī:OnInitDialog
* ���:�ֱ�â�� ����ɶ��� �̺�Ʈ�� �����Ѵ�.
*/
BOOL MoveToLineForm::OnInitDialog() {
	CDialog::OnInitDialog();

	Long currentLine;
	Long lineNumber;
	CString lineNumberInString;

	//������ ���� ���� ���Ѵ�.
	currentLine = this->notepannel->paper->GetCurrent();
	lineNumber = currentLine + 1;
	lineNumberInString.Format("%d", lineNumber);
	//������ ���� ���� ����Ѵ�.
	GetDlgItem(IDC_EDIT_LINENUMBER)->SetWindowTextA(lineNumberInString);

	((CEdit*)(GetDlgItem(IDC_EDIT_LINENUMBER)))->SetSel(0, -1, FALSE);
	GetDlgItem(IDC_EDIT_LINENUMBER)->SetFocus();

	return FALSE;
}

/*
* �Լ���Ī:OnClose
* ���:�ֱ�â�� �ݴ´�.
*/
void MoveToLineForm::OnClose() {
	this->EndDialog(0);
	this->notepannel->SetFocus();
}

/*
* �Լ���Ī:OnCancelButtonClicked
* ���:��ư�� Ŭ���������� �̺�Ʈ�� �����Ѵ�.
*/
void MoveToLineForm::OnCancelButtonClicked() {
	this->EndDialog(0);
	this->notepannel->SetFocus();
}

/*
* �Լ���Ī:OnMoveButtonClicked
* ���:��ư�� Ŭ���������� �̺�Ʈ�� �����Ѵ�.
*/
void MoveToLineForm::OnMoveButtonClicked() {
	Long pageLength;
	Long lineNumber;
	CString lineNumberWritten;
	CString lineNumberInString;

	Glyph* currentLine = NULL;
	int lineOrder;
	int charIndex;

	//������ �ִ� ���� ���Ѵ�.
	pageLength = this->notepannel->paper->GetLength();

	//�Էµ� ���ڸ� �д´�. 
	GetDlgItem(IDC_EDIT_LINENUMBER)->GetWindowTextA(lineNumberWritten);
	lineNumber = (Long)(_ttoi(lineNumberWritten));

	if (lineNumber <= pageLength) {
		//���̿��� �ش� �ٷ� �̵��Ѵ�.
		lineOrder = this->notepannel->paper->Move(lineNumber - 1);
		//�ٿ��� �� ������ �̵��Ѵ�.
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		charIndex = currentLine->First();

		//���� ��ġ�� ���� Ŭ������ �ʱ�ȭ�Ѵ�. 
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel, charIndex, lineOrder, charIndex, lineOrder);
		//������Ʈ ���� �Լ��� ȣ���Ѵ�.
		//ĳ���� ������Ʈ �Ѵ�. 
		this->notepannel->clientMoveCheck = TRUE;
		this->notepannel->Notify();
		//Ŭ���̾�Ʈ ���� �Լ��� ȣ���Ѵ�.
		this->notepannel->Invalidate(TRUE);

		this->EndDialog(0);
		this->notepannel->SetFocus();

		//ĳ���� ���̰��Ѵ�.
		this->notepannel->caret->ShowCaret();
	}
	else {
		AfxMessageBox(_T("�� ��ȣ�� ��ü �� ���� �ѽ��ϴ�."));

		lineNumberInString.Format("%d", pageLength);
		GetDlgItem(IDC_EDIT_LINENUMBER)->SetWindowTextA(lineNumberInString);

		((CEdit*)(GetDlgItem(IDC_EDIT_LINENUMBER)))->SetSel(0, -1, FALSE);
		GetDlgItem(IDC_EDIT_LINENUMBER)->SetFocus();

	}
}