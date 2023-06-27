//NewCommand.cpp
/*
* 파일명칭:NewCommand.cpp
* 기능:새로 만들기 커멘드
* 작성자:허지욱
* 작성일자:20221012
*/
#include "NewCommand.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "Document.h"
#include "Caret.h"
#include "DocumentVirtualSize.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Scroll.h"
#include "PageSetting.h"
#include "Select.h"
#include "MacroCommand.h"

#include "GlyphCreater.h"
#include "Paper.h"

#include <afxdlgs.h>

/*
* 함수명칭:NewCommand
* 기능:생성자
*/
NewCommand::NewCommand(Notepannel* notepannel) : notepannel(notepannel) {
}

/*
* 함수명칭:~NewCommand
* 기능:소멸자
*/
NewCommand::~NewCommand() {
}

/*
* 함수명칭:Execute
* 기능:적재하기 커멘드를 실행하다
*/
void NewCommand::Execute() {
	int messageReturn = -1;
	CString messageString;
	INT_PTR dialogRetrun;
	CString nameDefault;
	CString path;
	CString name;
	CString extention;
	CString windowTitle;
	Glyph* paper = NULL;
	Glyph* line = NULL;
	GlyphCreater glyphCreator;

	nameDefault.Format("%s.%s", this->notepannel->document->GetName().c_str(), this->notepannel->document->GetExtention().c_str());
	CFileDialog save(FALSE, _T("txt"), nameDefault,
		OFN_CREATEPROMPT | OFN_ENABLESIZING | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("텍스트문서 (*.txt)|*.txt|"), NULL, 0);
	CFileDialog load(TRUE, _T("txt"), nameDefault,
		OFN_ENABLESIZING | OFN_HIDEREADONLY,
		_T("텍스트문서 (*.txt)|*.txt|"), NULL, 0);


	if (this->notepannel->hasChanged == TRUE) {
		if (this->notepannel->isSaved == TRUE) {
			messageString.Format("변경내용을 %s\\%s.%s에 저장하시겠습니까?", this->notepannel->document->GetPath().c_str(), this->notepannel->document->GetName().c_str(), this->notepannel->document->GetExtention().c_str());
		}
		else {
			messageString.Format("변경내용을 %s.%s에 저장하시겠습니까?", this->notepannel->document->GetName().c_str(), this->notepannel->document->GetExtention().c_str());
		}

		//messageReturn = MessageBox(messageString, "메모장", MB_YESNOCANCEL);
		// 대체
		messageReturn = SaveMessageBox(this->notepannel->GetSafeHwnd(), messageString, _T("메모장"), MB_YESNOCANCEL);

		if (this->notepannel->isSaved == TRUE && messageReturn == IDYES) {
			//종이의 사본을 만들어 더미줄병합을 한다.
			paper = this->notepannel->paper;
			paper->MergeAllDummyLines();
			//기존 문서에 저장한다.
			this->notepannel->document->Save(paper);

			//저장했다는 표시를 한다. 
			this->notepannel->isSaved = TRUE;
			//변경되지 않았음을 표시한다.
			this->notepannel->hasChanged = FALSE;
			//윈도우의 제목을 갱신한다.
			windowTitle.Format("%s - Windows 메모장", this->notepannel->document->GetName().c_str());
			this->notepannel->notepad->SetWindowText(windowTitle);
		}
		else if (this->notepannel->isSaved == FALSE && messageReturn == IDYES) {
			dialogRetrun = save.DoModal();
			if (dialogRetrun == IDOK) {
				//종이의 사본을 만들어 더미줄병합을 한다.
				paper = this->notepannel->paper;
				paper->MergeAllDummyLines();

				path = save.GetFolderPath();
				name = save.GetFileTitle();
				extention = save.GetFileExt();
				//다른이름으로 저장한다. 
				delete this->notepannel->document;
				this->notepannel->document = new Document((LPCSTR)path, (LPCSTR)name, (LPCSTR)extention);
				this->notepannel->document->Save(paper);
				//저장했다는 표시를 한다. 
				this->notepannel->isSaved = TRUE;
				//변경되지 않았음을 표시한다.
				this->notepannel->hasChanged = FALSE;
				//윈도우의 제목을 갱신한다.
				windowTitle.Format("%s - Windows 메모장", this->notepannel->document->GetName().c_str());
				this->notepannel->notepad->SetWindowText(windowTitle);
			}
		}
	}

	if (messageReturn != IDCANCEL || messageReturn == -1) {
		//문서를 지운다.
		delete this->notepannel->document;
		//종이를 제거한다.
		delete this->notepannel->paper;
		//새 종이를 만든다.
		this->notepannel->paper = glyphCreator.Create("");
		//종이에 새 줄을 삽입한다.
		line = glyphCreator.Create("\r\n");
		this->notepannel->paper->Add(line);
		//맨 앞으로 이동한다.
		this->notepannel->paper->First();
		this->notepannel->paper->GetAt(0)->First();
		//선택하기를 초기화한다.
		delete this->notepannel->select;
		this->notepannel->select = new Select(notepannel);
		//실행취소/재실행된 내용을 제거한다. 
		delete this->notepannel->macroCommand;
		this->notepannel->macroCommand = new MacroCommand();

		//빈 문서를 만든다.
		this->notepannel->document = new Document();
		//문서 제목 상단에 제목을 출력한다.
		windowTitle.Format("%s - Windows 메모장", this->notepannel->document->GetName().c_str());
		this->notepannel->notepad->SetWindowText(windowTitle);
		//저장되었다는 표시를 내린다
		this->notepannel->isSaved = FALSE;
		//변경되지 않았음을 표시한다. 
		this->notepannel->hasChanged = FALSE;
		//문서에서 내용의 업데이트를 했음을 표시한다. 
		this->notepannel->documentUploaded = TRUE;
		this->notepannel->clientMoveCheck = TRUE;
		//메모장의 업데이트를 호출한다.
		this->notepannel->Notify();
		//윈도우 갱신 함수를 호출한다.
		this->notepannel->Invalidate(TRUE);
		//캐럿을 표시한다.
		this->notepannel->caret->ShowCaret();

		//페이지 설정을 초기화한다. 
		CString fileName;
		fileName.Format("%s.%s", this->notepannel->document->GetName().c_str(), this->notepannel->document->GetExtention().c_str());
		delete this->notepannel->pageSetting;
		this->notepannel->pageSetting = new PageSetting(this->notepannel, (string)(fileName));

	}
}