//CloseCommand.cpp
/*
* 파일명칭:CloseCommand.cpp
* 기능:닫기 커멘드
* 작성자:허지욱
* 작성일자:20220826
*/
#include "CloseCommand.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "Document.h"
#include "Caret.h"
#include "Paper.h"
#include <afxdlgs.h>

/*
* 함수명칭:CloseCommand
* 기능:생성자
*/
CloseCommand::CloseCommand(Notepannel* notepannel) : notepannel(notepannel) {
}

/*
* 함수명칭:~CloseCommand
* 기능:소멸자
*/
CloseCommand::~CloseCommand() {
}

/*
* 함수명칭:Execute
* 기능:닫기 커멘드를 실행하다
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


		if (this->notepannel->isSaved == TRUE && messageReturn == IDYES) { //저장하기
			//종이의 사본을 만들어 더미줄병합을 한다.
			paper = this->notepannel->paper;
			paper->MergeAllDummyLines();

			//기존 문서에 저장한다.
			this->notepannel->document->Save(paper);

			//저장했다는 표시를 한다. 
			this->notepannel->isSaved = TRUE;
			//변경되지 않았음을 표시한다.
			this->notepannel->hasChanged = FALSE;
			//창을 제거한다.
			this->notepannel->notepad->DestroyWindow();
		}
		else if (this->notepannel->isSaved == FALSE && messageReturn == IDYES) { //다른이름으로 저장하기
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
				//창을 제거한다.
				this->notepannel->notepad->DestroyWindow();
			}
		}
		else if (messageReturn == IDNO) {
			//창을 제거한다.
			this->notepannel->notepad->DestroyWindow();
		}
	}
	else {
		//창을 제거한다.
		this->notepannel->notepad->DestroyWindow();
	}
}