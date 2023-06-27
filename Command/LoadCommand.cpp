//LoadCommand.cpp
/*
* ���ϸ�Ī:LoadCommand.cpp
* ���:�����ϱ� Ŀ���
* �ۼ���:������
* �ۼ�����:20220826
*/
#include "LoadCommand.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "Paper.h"
#include "Document.h"
#include "Caret.h"
#include "DocumentVirtualSize.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Scroll.h"
#include "Select.h"
#include "PageSetting.h"
#include <afxdlgs.h>
#include "MacroCommand.h"

/*
* �Լ���Ī:LoadCommand
* ���:������
*/
LoadCommand::LoadCommand(Notepannel* notepannel) : notepannel(notepannel) {
}

/*
* �Լ���Ī:~LoadCommand
* ���:�Ҹ���
*/
LoadCommand::~LoadCommand() {
}

/*
* �Լ���Ī:Execute
* ���:�����ϱ� Ŀ��带 �����ϴ�
*/
void LoadCommand::Execute() {
	int messageReturn = -1;
	CString messageString;
	INT_PTR dialogRetrun;
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
	CFileDialog load(TRUE, _T("txt"), nameDefault,
		OFN_ENABLESIZING | OFN_HIDEREADONLY,
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

		if (this->notepannel->isSaved == TRUE && messageReturn == IDYES) {
			//������ �纻�� ����� �����ٺ����� �Ѵ�.
			paper = this->notepannel->paper;
			paper->MergeAllDummyLines();
			//���� ������ �����Ѵ�.
			this->notepannel->document->Save(paper);

			//�����ߴٴ� ǥ�ø� �Ѵ�. 
			this->notepannel->isSaved = TRUE;
			//������� �ʾ����� ǥ���Ѵ�.
			this->notepannel->hasChanged = FALSE;
			//�������� ������ �����Ѵ�.
			windowTitle.Format("%s - Windows �޸���", this->notepannel->document->GetName().c_str());
			this->notepannel->notepad->SetWindowText(windowTitle);
		}
		else if (this->notepannel->isSaved == FALSE && messageReturn == IDYES) {
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
				//�������� ������ �����Ѵ�.
				windowTitle.Format("%s - Windows �޸���", this->notepannel->document->GetName().c_str());
				this->notepannel->notepad->SetWindowText(windowTitle);
			}
		}
	}

	if (messageReturn != IDCANCEL || messageReturn == -1) {

		dialogRetrun = load.DoModal();

		if (dialogRetrun == IDOK) {
			path = load.GetFolderPath();
			name = load.GetFileTitle();
			extention = load.GetFileExt();
			delete this->notepannel->document;
			this->notepannel->document = new Document((LPCSTR)path, (LPCSTR)name, (LPCSTR)extention);
			delete this->notepannel->paper;
			this->notepannel->paper = this->notepannel->document->Load();
			//����Ǿ��ٴ� ǥ�ø� �Ѵ�. 
			this->notepannel->isSaved = TRUE;
			//������� �ʾ����� ǥ���Ѵ�. 
			this->notepannel->hasChanged = FALSE;
			//�������� ������ �����Ѵ�.
			windowTitle.Format("%s - Windows �޸���", this->notepannel->document->GetName().c_str());
			this->notepannel->notepad->SetWindowText(windowTitle);

			//������ ������ �ʱ�ȭ�Ѵ�. 
			CString fileName;
			fileName.Format("%s.%s", this->notepannel->document->GetName().c_str(), this->notepannel->document->GetExtention().c_str());
			delete this->notepannel->pageSetting;
			this->notepannel->pageSetting = new PageSetting(this->notepannel, (string)(fileName));


			//������ �� ������ �̵��Ѵ�
			this->notepannel->paper->First();
			this->notepannel->paper->GetAt(0)->First();
			//�����ϱ⸦ �ʱ�ȭ�Ѵ�.
			delete this->notepannel->select;
			this->notepannel->select = new Select(notepannel);
			//�������/������ ������ �����Ѵ�. 
			delete this->notepannel->macroCommand;
			this->notepannel->macroCommand = new MacroCommand();

			//�������� ������ ������Ʈ�� ������ ǥ���Ѵ�. 
			this->notepannel->documentUploaded = TRUE;
			//Ŭ���̾�Ʈ�� �̵��� �ʿ����� ǥ���Ѵ�.
			this->notepannel->clientMoveCheck = TRUE;
			//�޸����� ������Ʈ�� ȣ���Ѵ�.
			this->notepannel->Notify();
			this->notepannel->documentUploaded = FALSE;
			//Ŭ���̾�Ʈ ȭ���� �����Ѵ�.
			this->notepannel->Invalidate(TRUE);
			//ĳ���� ǥ���Ѵ�. 
			this->notepannel->caret->ShowCaret();

			//
			this->notepannel->hasLoaded = TRUE;



		}
	}
}