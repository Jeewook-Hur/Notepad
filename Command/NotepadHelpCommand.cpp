//NotepadHelpCommand.cpp
/*
* 파일명칭:NotepadHelpCommand.cpp
* 기능:도움말 보기 메뉴 커멘드
* 작성자:허지욱
* 작성일자:20230215
*/
#include "NotepadHelpCommand.h"
#include "Notepannel.h"
#include "Notepad.h"
#include<string>
using namespace std;


/*
* 함수명칭:NotepadHelpCommand
* 기능:생성자
*/
NotepadHelpCommand::NotepadHelpCommand(Notepannel* notepannel) : notepannel(notepannel) {
}

/*
* 함수명칭:~NotepadHelpCommand
* 기능:소멸자
*/
NotepadHelpCommand::~NotepadHelpCommand() {
}

/*
* 함수명칭:Execute
* 기능:닫기 커멘드를 실행하다
*/
void NotepadHelpCommand::Execute() {
	
	CString strChm = "NotepadHelp20230224.chm";

	ShellExecuteA(this->notepannel->notepad->m_hWnd, "open", strChm, 0, 0, SW_SHOWDEFAULT);

}