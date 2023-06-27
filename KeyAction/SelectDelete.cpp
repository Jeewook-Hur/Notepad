//SelectDelete.cpp
/*
* 파일명칭:SelectDelete.cpp
* 기능:선택영역을 지울때의 전략
* 작성자:허지욱
* 작성일자:2022/11/15
*/
#include "SelectDelete.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "Caret.h"
#include "Document.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"

/*
* 함수명칭:SelectDelete
* 기능:생성자
*/
SelectDelete::SelectDelete(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~SelectDelete
* 기능:소멸자
*/
SelectDelete::~SelectDelete() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void SelectDelete::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* frontLine = NULL;
	Glyph* endLine = NULL;
	int frontLineOrder = this->notepannel->select->frontLineOrder;
	int endLineOrder = this->notepannel->select->endLineOrder;
	int frontCharIndex = this->notepannel->select->frontXIndex;
	int endCharIndex = this->notepannel->select->endXIndex;
	int frontLength;
	//맨 앞줄을 가져온다.
	frontLine = this->notepannel->paper->GetAt(frontLineOrder);

	if (!(frontLineOrder == endLineOrder && frontCharIndex == endCharIndex)) {//선택된 영역이 있으면
		if (frontLineOrder == endLineOrder) {//맨앞줄과 맨뒤 줄이 같으면 해당 줄의 맨앞부터 끝까지 지운다.
			frontLine->Remove(frontCharIndex + 1, endCharIndex);
		}
		else {//맨앞과 맨뒤 줄이 다르면
			//맨앞 줄에서 선택된 부분부터 끝까지 지운다.
			frontLength = frontLine->GetLength();
			frontLine->Remove(frontCharIndex + 1, frontLength - 1);
			//끝의 줄을 가져온다.
			endLine = this->notepannel->paper->GetAt(endLineOrder);
			//끝의 줄에서 맨 앞부터 선택된 부분까지 지운다.
			endLine->Remove(0, endCharIndex);
			//맨 앞 줄의 끝에 끝의 줄을 합친다.
			frontLine->Add(endLine, frontCharIndex + 1);
			//선택한 다음 줄부터 마지막 줄까지 지운다.
			this->notepannel->paper->Remove(frontLineOrder + 1, endLineOrder);
		}
		//선택 위치의 맨 앞 위치로 이동한다.
		frontLineOrder = this->notepannel->paper->Move(frontLineOrder);
		frontLine = this->notepannel->paper->GetAt(frontLineOrder);
		frontLine->Move(frontCharIndex);
		//선택영역을 초기화한다.
		delete this->notepannel->select;
		this->notepannel->select = new Select(notepannel);
		//선택되었다는 표시를 내린다. 
		this->notepannel->isSelected = FALSE;

		//문서가 변경되었음을 표시한다. 
		this->notepannel->hasChanged = TRUE;
		//윈도우의 제목을 갱신한다.
		CString windowTitle;
		windowTitle.Format("*%s - Windows 메모장", this->notepannel->document->GetName().c_str());
		this->notepannel->notepad->SetWindowText(windowTitle);

		this->notepannel->documentUploaded = TRUE;
		this->notepannel->clientMoveCheck = TRUE;
		this->notepannel->Notify();
		this->notepannel->Invalidate(TRUE);
		this->notepannel->caret->ShowCaret();
	}
}