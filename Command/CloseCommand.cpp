//CloseCommand.cpp
/*
* ���ϸ�Ī:CloseCommand.cpp
* ���:�ݱ� Ŀ���
* �ۼ���:������
* �ۼ�����:20220826
*/
#include "CloseCommand.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "Document.h"
#include "Caret.h"
#include "Paper.h"
#include <afxdlgs.h>

/*
* �Լ���Ī:CloseCommand
* ���:������
*/
CloseCommand::CloseCommand(Notepannel* notepannel) : notepannel(notepannel) {
}

/*
* �Լ���Ī:~CloseCommand
* ���:�Ҹ���
*/
CloseCommand::~CloseCommand() {
}

/*
* �Լ���Ī:Execute
* ���:�ݱ� Ŀ��带 �����ϴ�
*/
void CloseCommand::Execute() {
	int messageReturn;
	CString messageString;
	INT_PTR dialogRetrun = -1;
	CString nameDefault;
	CString path;
	CString name;
	CString extention;
	CString windowTitle;
	Glyph* paper = NULL;

	nameDefault.Format("%s.%s", this->notepannel->document->GetName().c_str(), this->notepannel->document->GetExtention().c_str());
	CFileDialog save(FALSE, _T("txt"), nameDefault,
		OFN_CREATEPROMPT | OFN_ENABLESIZING | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("�ؽ�Ʈ���� (*.txt)|*.txt|"), NULL, 0);

	if (this->notepannel->hasChanged == TRUE) {
		if (this->notepannel->isSaved == TRUE) {
			messageString.Format("���泻���� %s\\%s.%s�� �����Ͻðڽ��ϱ�?", this->notepannel->document->GetPath().c_str(), this->notepannel->document->GetName().c_str(), this->notepannel->document->GetExtention().c_str());
		}
		else {
			messageString.Format("���泻���� %s.%s�� �����Ͻðڽ��ϱ�?", this->notepannel->document->GetName().c_str(), this->notepannel->document->GetExtention().c_str());
		}

		//messageReturn = MessageBox(messageString, "�޸���", MB_YESNOCANCEL);
		// ��ü
		messageReturn = SaveMessageBox(this->notepannel->GetSafeHwnd(), messageString, _T("�޸���"), MB_YESNOCANCEL);


		if (this->notepannel->isSaved == TRUE && messageReturn == IDYES) { //�����ϱ�
			//������ �纻�� ����� �����ٺ����� �Ѵ�.
			paper = this->notepannel->paper;
			paper->MergeAllDummyLines();

			//���� ������ �����Ѵ�.
			this->notepannel->document->Save(paper);

			//�����ߴٴ� ǥ�ø� �Ѵ�. 
			this->notepannel->isSaved = TRUE;
			//������� �ʾ����� ǥ���Ѵ�.
			this->notepannel->hasChanged = FALSE;
			//â�� �����Ѵ�.
			this->notepannel->notepad->DestroyWindow();
		}
		else if (this->notepannel->isSaved == FALSE && messageReturn == IDYES) { //�ٸ��̸����� �����ϱ�
			dialogRetrun = save.DoModal();
			if (dialogRetrun == IDOK) {
				//������ �纻�� ����� �����ٺ����� �Ѵ�.
				paper = this->notepannel->paper;
				paper->MergeAllDummyLines();

				path = save.GetFolderPath();
				name = save.GetFileTitle();
				extention = save.GetFileExt();
				//�ٸ��̸����� �����Ѵ�. 
				delete this->notepannel->document;
				this->notepannel->document = new Document((LPCSTR)path, (LPCSTR)name, (LPCSTR)extention);
				this->notepannel->document->Save(paper);
				//�����ߴٴ� ǥ�ø� �Ѵ�. 
				this->notepannel->isSaved = TRUE;
				//������� �ʾ����� ǥ���Ѵ�.
				this->notepannel->hasChanged = FALSE;
				//â�� �����Ѵ�.
				this->notepannel->notepad->DestroyWindow();
			}
		}
		else if (messageReturn == IDNO) {
			//â�� �����Ѵ�.
			this->notepannel->notepad->DestroyWindow();
		}
	}
	else {
		//â�� �����Ѵ�.
		this->notepannel->notepad->DestroyWindow();
	}
}