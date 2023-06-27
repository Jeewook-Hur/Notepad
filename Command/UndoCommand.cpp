//UndoCommand.cpp
/*
* 파일명칭:UndoCommand.cpp
* 기능:실행취소 하는 커멘드
* 작성자:허지욱
* 작성일자:2022/11/29
*/
#include "UndoCommand.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "MacroCommand.h"
#include "Caret.h"
#include "Document.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"

/*
* 함수명칭:UndoCommand
* 기능:생성자
*/
UndoCommand::UndoCommand(Notepannel* notepannel):notepannel(notepannel) {
}

/*
* 함수명칭:~UndoCommand
* 기능:소멸자
*/
UndoCommand::~UndoCommand() {
}

/*
* 함수명칭:Execute
* 기능:커멘드를 실행한다.
*/
void UndoCommand::Execute() {
	int result;

	if (this->notepannel->macroCommand->ToUndo() == true) {
		result = this->notepannel->macroCommand->Undo();

		if (result == 0) {
			//내용이 변경되었다는 플래그를 띄운다.
			this->notepannel->hasChanged = TRUE;
			//윈도우의 제목을 갱신한다.
			CString windowTitle;
			windowTitle.Format("*%s - Windows 메모장", this->notepannel->document->GetName().c_str());
			this->notepannel->notepad->SetWindowText(windowTitle);
		}
		else if (result == 1) {
			//내용이 변경되었다는 플래그를 내린다
			this->notepannel->hasChanged = FALSE;
			//윈도우의 제목을 갱신한다.
			CString windowTitle;
			windowTitle.Format("%s - Windows 메모장", this->notepannel->document->GetName().c_str());
			this->notepannel->notepad->SetWindowText(windowTitle);
		}


		//업데이트를 한다(위치, 내용 등)
		//this->notepannel->hasChanged = TRUE;
		this->notepannel->documentUploaded = TRUE;
		this->notepannel->clientMoveCheck = TRUE;
		this->notepannel->Notify();
		//클라이언트를 갱신하다.
		this->notepannel->Invalidate(TRUE);
		//캐럿을 출력한다.
		this->notepannel->caret->ShowCaret();
	}
#if 0
	else { //맨 처음을 돌아오면
		//내용이 변경되었다는 플래그를 내린다
		this->notepannel->hasChanged = FALSE;
		//윈도우의 제목을 갱신한다.
		CString windowTitle;
		windowTitle.Format("%s - Windows 메모장", this->notepannel->document->GetName().c_str());
		this->notepannel->notepad->SetWindowText(windowTitle);
	}
#endif
}

/*
* 함수명칭:UnExecute
* 기능:커멘드를 실행취소한다.
*/
void UndoCommand::UnExecute() {
	int result;
	if (this->notepannel->macroCommand->ToRedo() == true) {
		result = this->notepannel->macroCommand->Redo();

		if (result == 0) {
			//내용이 변경되었다는 플래그를 띄운다.
			this->notepannel->hasChanged = TRUE;
			//윈도우의 제목을 갱신한다.
			CString windowTitle;
			windowTitle.Format("*%s - Windows 메모장", this->notepannel->document->GetName().c_str());
			this->notepannel->notepad->SetWindowText(windowTitle);
		}
		else if (result == 1) {
			//내용이 변경되었다는 플래그를 내린다
			this->notepannel->hasChanged = FALSE;
			//윈도우의 제목을 갱신한다.
			CString windowTitle;
			windowTitle.Format("%s - Windows 메모장", this->notepannel->document->GetName().c_str());
			this->notepannel->notepad->SetWindowText(windowTitle);
		}

		//업데이트를 한다(위치, 내용 등)
		//this->notepannel->hasChanged = TRUE;
		this->notepannel->documentUploaded = TRUE;
		this->notepannel->clientMoveCheck = TRUE;
		this->notepannel->Notify();
		//클라이언트를 갱신하다.
		this->notepannel->Invalidate(TRUE);
		//캐럿을 출력한다.
		this->notepannel->caret->ShowCaret();
	}

#if 0
	//삽입한 내용을 선택한다. 
	delete this->notepannel->select;
	this->notepannel->select = new Select(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);
	//선택되었다는 표시를 올린다. 
	this->notepannel->isSelected = FALSE;
#endif
}