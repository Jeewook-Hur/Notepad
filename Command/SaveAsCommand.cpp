//SaveAsCommand.cpp
/*
* ���ϸ�Ī:SaveAsCommand.cpp
* ���:�ٸ��̸����� �����ϱ� Ŀ���
* �ۼ���:������
* �ۼ�����:20220826
*/
#include "SaveAsCommand.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "Document.h"
#include "MacroCommand.h"
#include "PageSetting.h"
#include "Paper.h"
#include <afxdlgs.h>

/*
* �Լ���Ī:SaveAsCommand
* ���:������
*/
SaveAsCommand::SaveAsCommand(Notepannel* notepannel) : notepannel(notepannel) {
}

/*
* �Լ���Ī:~SaveAsCommand
* ���:�Ҹ���
*/
SaveAsCommand::~SaveAsCommand() {
}

/*
* �Լ���Ī:Execute
* ���:�ٸ��̸����� �����ϱ� Ŀ��带 �����ϴ�
*/
void SaveAsCommand::Execute() {
	CString nameDefault;
	Glyph* paper = NULL;
	nameDefault.Format("%s.%s", this->notepannel->document->GetName().c_str(), this->notepannel->document->GetExtention().c_str());

	CFileDialog cFileDialog(FALSE, _T("txt"), nameDefault,
		OFN_CREATEPROMPT | OFN_ENABLESIZING | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("�ؽ�Ʈ���� (*.txt)|*.txt|"), NULL, 0);
	//(FALSE, _T("my"));
	INT_PTR dialogRetrun;
	CString path;
	CString name;
	CString extention;
	CString windowTitle;

	dialogRetrun = cFileDialog.DoModal();
	if (dialogRetrun == IDOK) {
		//������ �纻�� ����� �����ٺ����� �Ѵ�.
		paper = this->notepannel->paper->Clone();
		paper->MergeAllDummyLines();

		path = cFileDialog.GetFolderPath();
		name = cFileDialog.GetFileTitle();
		extention = cFileDialog.GetFileExt();
		delete this->notepannel->document;
		this->notepannel->document = new Document((LPCSTR)path, (LPCSTR)name, (LPCSTR)extention);
		this->notepannel->document->Save(paper);

		//�纻�� �����Ѵ�.
		delete paper;

		//�����ߴٴ� ǥ�ø� �Ѵ�. 
		this->notepannel->isSaved = TRUE;
		//������� �ʾ����� ǥ���Ѵ�.
		this->notepannel->hasChanged = FALSE;
		//�ǵ������� ���������� �ʱ�ȭ�Ѵ�.
		this->notepannel->macroCommand->ChangeSavePoint();
		//�������� ������ �����Ѵ�.
		windowTitle.Format("%s - Windows �޸���", this->notepannel->document->GetName().c_str());
		this->notepannel->notepad->SetWindowText(windowTitle);

		//������ ������ �ʱ�ȭ�Ѵ�. 
		CString fileName;
		fileName.Format("%s.%s", this->notepannel->document->GetName().c_str(), this->notepannel->document->GetExtention().c_str());
		delete this->notepannel->pageSetting;
		this->notepannel->pageSetting = new PageSetting(this->notepannel, (string)(fileName));

	}
}