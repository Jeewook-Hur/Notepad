//AboutNotepadCommand.cpp
/*
* 파일명칭:AboutNotepadCommand.cpp
* 기능:메모장 정보 메뉴 커멘드
* 작성자:허지욱
* 작성일자:20230215
*/
#include "AboutNotepadCommand.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "AboutNotepadForm.h"


/*
* 함수명칭:AboutNotepadCommand
* 기능:생성자
*/
AboutNotepadCommand::AboutNotepadCommand(Notepannel* notepannel) : notepannel(notepannel) {
}

/*
* 함수명칭:~AboutNotepadCommand
* 기능:소멸자
*/
AboutNotepadCommand::~AboutNotepadCommand() {
}

/*
* 함수명칭:Execute
* 기능:닫기 커멘드를 실행하다
*/
void AboutNotepadCommand::Execute() {
	AboutNotepadForm aboutNotepadForm(this->notepannel, this->notepannel);
	aboutNotepadForm.DoModal();

	//AfxMessageBox(_T("메모장 정보\r\n<<내용입력하기>>\r\n제작자:허지욱\r\n다이얼로그 박스로..."));
#if 0
	CString lpText = "Windows 메모장\r\n제작자:허지욱\r\nver 1.0";
	CString lpCaption = "메모장 정보";

	MessageBoxA(
		this->notepannel->notepad->m_hWnd,
		lpText,
		lpCaption,
		MB_OK | MB_ICONQUESTION
	);
#endif
}