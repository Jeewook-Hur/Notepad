//NotepadHelpCommand.cpp
/*
* ���ϸ�Ī:NotepadHelpCommand.cpp
* ���:���� ���� �޴� Ŀ���
* �ۼ���:������
* �ۼ�����:20230215
*/
#include "NotepadHelpCommand.h"
#include "Notepannel.h"
#include "Notepad.h"
#include<string>
using namespace std;


/*
* �Լ���Ī:NotepadHelpCommand
* ���:������
*/
NotepadHelpCommand::NotepadHelpCommand(Notepannel* notepannel) : notepannel(notepannel) {
}

/*
* �Լ���Ī:~NotepadHelpCommand
* ���:�Ҹ���
*/
NotepadHelpCommand::~NotepadHelpCommand() {
}

/*
* �Լ���Ī:Execute
* ���:�ݱ� Ŀ��带 �����ϴ�
*/
void NotepadHelpCommand::Execute() {
	
	CString strChm = "NotepadHelp20230224.chm";

	ShellExecuteA(this->notepannel->notepad->m_hWnd, "open", strChm, 0, 0, SW_SHOWDEFAULT);

}