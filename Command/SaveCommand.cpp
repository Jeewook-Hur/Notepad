//SaveCommand.cpp
/*
* 파일명칭:SaveCommand.cpp
* 기능:저장하기 커멘드
* 작성자:허지욱
* 작성일자:20220826
*/
#include "SaveCommand.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "Document.h"
#include "MacroCommand.h"
#include "PageSetting.h"
#include "Paper.h"
#include <afxdlgs.h>

/*
* 함수명칭:SaveCommand
* 기능:생성자
*/
SaveCommand::SaveCommand(Notepannel* notepannel) : notepannel(notepannel) {
}

/*
* 함수명칭:~SaveCommand
* 기능:소멸자
*/
SaveCommand::~SaveCommand() {
}

/*
* 함수명칭:Execute
* 기능:저장하기 커멘드를 실행하다
*/
void SaveCommand::Execute() {
	CString nameDefault;
	nameDefault.Format("%s.%s", this->notepannel->document->GetName().c_str(), this->notepannel->document->GetExtention().c_str());
	INT_PTR dialogRetrun;
	CString path;
	CString name;
	CString extention;
	CString windowTitle;
	Glyph* paper = NULL;

	if (this->notepannel->isSaved == FALSE) {
		CFileDialog cFileDialog(FALSE, _T("txt"), nameDefault,
			OFN_CREATEPROMPT | OFN_ENABLESIZING | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			_T("텍스트문서 (*.txt)|*.txt|"), NULL, 0);
		dialogRetrun = cFileDialog.DoModal();
		if (dialogRetrun == IDOK) {
			//종이의 사본을 만들어 더미줄병합을 한다.
			paper = this->notepannel->paper->Clone();
			paper->MergeAllDummyLines();

			path = cFileDialog.GetFolderPath();
			name = cFileDialog.GetFileTitle();
			extention = cFileDialog.GetFileExt();

			delete this->notepannel->document;
			this->notepannel->document = new Document((LPCSTR)path, (LPCSTR)name, (LPCSTR)extention);
			this->notepannel->document->Save(paper);
			//사본을 제거한다.
			delete paper;
			//저장했다는 표시를 한다. 
			this->notepannel->isSaved = TRUE;
			//변경되지 않았음을 표시한다.
			this->notepannel->hasChanged = FALSE;
			//되돌리기의 저장지점을 초기화한다.
			this->notepannel->macroCommand->ChangeSavePoint();

			//윈도우의 제목을 갱신한다.
			windowTitle.Format("%s - Windows 메모장", (LPCSTR)name);
			this->notepannel->notepad->SetWindowText(windowTitle);


			//페이지 설정을 초기화한다. 
			CString fileName;
			fileName.Format("%s.%s", this->notepannel->document->GetName().c_str(), this->notepannel->document->GetExtention().c_str());
			delete this->notepannel->pageSetting;
			this->notepannel->pageSetting = new PageSetting(this->notepannel, (string)(fileName));

		}
	}
	else {
		//종이의 사본을 만들어 더미줄병합을 한다.
		paper = this->notepannel->paper->Clone();
		paper->MergeAllDummyLines();
		this->notepannel->document->Save(paper);
		//사본을 제거한다.
		delete paper;
		//저장했다는 표시를 한다. 
		this->notepannel->isSaved = TRUE;
		//변경되지 않았음을 표시한다.
		this->notepannel->hasChanged = FALSE;
		//되돌리기의 저장지점을 초기화한다.
		this->notepannel->macroCommand->ChangeSavePoint();
		//윈도우의 제목을 갱신한다.
		windowTitle.Format("%s - Windows 메모장", this->notepannel->document->GetName().c_str());
		this->notepannel->notepad->SetWindowText(windowTitle);
	}
}
