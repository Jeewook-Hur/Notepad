//AboutNotepadCommand.cpp
/*
* ���ϸ�Ī:AboutNotepadCommand.cpp
* ���:�޸��� ���� �޴� Ŀ���
* �ۼ���:������
* �ۼ�����:20230215
*/
#include "AboutNotepadCommand.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "AboutNotepadForm.h"


/*
* �Լ���Ī:AboutNotepadCommand
* ���:������
*/
AboutNotepadCommand::AboutNotepadCommand(Notepannel* notepannel) : notepannel(notepannel) {
}

/*
* �Լ���Ī:~AboutNotepadCommand
* ���:�Ҹ���
*/
AboutNotepadCommand::~AboutNotepadCommand() {
}

/*
* �Լ���Ī:Execute
* ���:�ݱ� Ŀ��带 �����ϴ�
*/
void AboutNotepadCommand::Execute() {
	AboutNotepadForm aboutNotepadForm(this->notepannel, this->notepannel);
	aboutNotepadForm.DoModal();

	//AfxMessageBox(_T("�޸��� ����\r\n<<�����Է��ϱ�>>\r\n������:������\r\n���̾�α� �ڽ���..."));
#if 0
	CString lpText = "Windows �޸���\r\n������:������\r\nver 1.0";
	CString lpCaption = "�޸��� ����";

	MessageBoxA(
		this->notepannel->notepad->m_hWnd,
		lpText,
		lpCaption,
		MB_OK | MB_ICONQUESTION
	);
#endif
}