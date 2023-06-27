//MoveToLineForm.cpp
/*
* 파일명칭:MoveToLineForm.cpp
* 기능:줄 이동 창 창
* 작성자:허지욱
* 작성일자:2023/2/6
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
* 함수명칭:MoveToLineForm
* 기능:생성자
*/
MoveToLineForm::MoveToLineForm(CWnd* parent, Notepannel* notepannel)
	:CDialog(MoveToLineForm::IDD, parent), notepannel(notepannel) {
}

/*
* 함수명칭:OnInitDialog
* 기능:넣기창이 실행될때의 이벤트를 실행한다.
*/
BOOL MoveToLineForm::OnInitDialog() {
	CDialog::OnInitDialog();

	Long currentLine;
	Long lineNumber;
	CString lineNumberInString;

	//종이의 현재 행을 구한다.
	currentLine = this->notepannel->paper->GetCurrent();
	lineNumber = currentLine + 1;
	lineNumberInString.Format("%d", lineNumber);
	//종이의 현재 행을 출력한다.
	GetDlgItem(IDC_EDIT_LINENUMBER)->SetWindowTextA(lineNumberInString);

	((CEdit*)(GetDlgItem(IDC_EDIT_LINENUMBER)))->SetSel(0, -1, FALSE);
	GetDlgItem(IDC_EDIT_LINENUMBER)->SetFocus();

	return FALSE;
}

/*
* 함수명칭:OnClose
* 기능:넣기창을 닫는다.
*/
void MoveToLineForm::OnClose() {
	this->EndDialog(0);
	this->notepannel->SetFocus();
}

/*
* 함수명칭:OnCancelButtonClicked
* 기능:버튼을 클릭했을때의 이벤트를 실행한다.
*/
void MoveToLineForm::OnCancelButtonClicked() {
	this->EndDialog(0);
	this->notepannel->SetFocus();
}

/*
* 함수명칭:OnMoveButtonClicked
* 기능:버튼을 클릭했을때의 이벤트를 실행한다.
*/
void MoveToLineForm::OnMoveButtonClicked() {
	Long pageLength;
	Long lineNumber;
	CString lineNumberWritten;
	CString lineNumberInString;

	Glyph* currentLine = NULL;
	int lineOrder;
	int charIndex;

	//종이의 최대 줄을 구한다.
	pageLength = this->notepannel->paper->GetLength();

	//입력된 숫자를 읽는다. 
	GetDlgItem(IDC_EDIT_LINENUMBER)->GetWindowTextA(lineNumberWritten);
	lineNumber = (Long)(_ttoi(lineNumberWritten));

	if (lineNumber <= pageLength) {
		//종이에서 해당 줄로 이동한다.
		lineOrder = this->notepannel->paper->Move(lineNumber - 1);
		//줄에서 맨 앞으로 이동한다.
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		charIndex = currentLine->First();

		//현재 위치로 선택 클래스를 초기화한다. 
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel, charIndex, lineOrder, charIndex, lineOrder);
		//업데이트 갱신 함수를 호출한다.
		//캐럿을 업데이트 한다. 
		this->notepannel->clientMoveCheck = TRUE;
		this->notepannel->Notify();
		//클라이언트 갱신 함수를 호출한다.
		this->notepannel->Invalidate(TRUE);

		this->EndDialog(0);
		this->notepannel->SetFocus();

		//캐럿을 보이게한다.
		this->notepannel->caret->ShowCaret();
	}
	else {
		AfxMessageBox(_T("줄 번호가 전체 줄 수를 넘습니다."));

		lineNumberInString.Format("%d", pageLength);
		GetDlgItem(IDC_EDIT_LINENUMBER)->SetWindowTextA(lineNumberInString);

		((CEdit*)(GetDlgItem(IDC_EDIT_LINENUMBER)))->SetSel(0, -1, FALSE);
		GetDlgItem(IDC_EDIT_LINENUMBER)->SetFocus();

	}
}