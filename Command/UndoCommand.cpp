//UndoCommand.cpp
/*
* ���ϸ�Ī:UndoCommand.cpp
* ���:������� �ϴ� Ŀ���
* �ۼ���:������
* �ۼ�����:2022/11/29
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
* �Լ���Ī:UndoCommand
* ���:������
*/
UndoCommand::UndoCommand(Notepannel* notepannel):notepannel(notepannel) {
}

/*
* �Լ���Ī:~UndoCommand
* ���:�Ҹ���
*/
UndoCommand::~UndoCommand() {
}

/*
* �Լ���Ī:Execute
* ���:Ŀ��带 �����Ѵ�.
*/
void UndoCommand::Execute() {
	int result;

	if (this->notepannel->macroCommand->ToUndo() == true) {
		result = this->notepannel->macroCommand->Undo();

		if (result == 0) {
			//������ ����Ǿ��ٴ� �÷��׸� ����.
			this->notepannel->hasChanged = TRUE;
			//�������� ������ �����Ѵ�.
			CString windowTitle;
			windowTitle.Format("*%s - Windows �޸���", this->notepannel->document->GetName().c_str());
			this->notepannel->notepad->SetWindowText(windowTitle);
		}
		else if (result == 1) {
			//������ ����Ǿ��ٴ� �÷��׸� ������
			this->notepannel->hasChanged = FALSE;
			//�������� ������ �����Ѵ�.
			CString windowTitle;
			windowTitle.Format("%s - Windows �޸���", this->notepannel->document->GetName().c_str());
			this->notepannel->notepad->SetWindowText(windowTitle);
		}


		//������Ʈ�� �Ѵ�(��ġ, ���� ��)
		//this->notepannel->hasChanged = TRUE;
		this->notepannel->documentUploaded = TRUE;
		this->notepannel->clientMoveCheck = TRUE;
		this->notepannel->Notify();
		//Ŭ���̾�Ʈ�� �����ϴ�.
		this->notepannel->Invalidate(TRUE);
		//ĳ���� ����Ѵ�.
		this->notepannel->caret->ShowCaret();
	}
#if 0
	else { //�� ó���� ���ƿ���
		//������ ����Ǿ��ٴ� �÷��׸� ������
		this->notepannel->hasChanged = FALSE;
		//�������� ������ �����Ѵ�.
		CString windowTitle;
		windowTitle.Format("%s - Windows �޸���", this->notepannel->document->GetName().c_str());
		this->notepannel->notepad->SetWindowText(windowTitle);
	}
#endif
}

/*
* �Լ���Ī:UnExecute
* ���:Ŀ��带 ��������Ѵ�.
*/
void UndoCommand::UnExecute() {
	int result;
	if (this->notepannel->macroCommand->ToRedo() == true) {
		result = this->notepannel->macroCommand->Redo();

		if (result == 0) {
			//������ ����Ǿ��ٴ� �÷��׸� ����.
			this->notepannel->hasChanged = TRUE;
			//�������� ������ �����Ѵ�.
			CString windowTitle;
			windowTitle.Format("*%s - Windows �޸���", this->notepannel->document->GetName().c_str());
			this->notepannel->notepad->SetWindowText(windowTitle);
		}
		else if (result == 1) {
			//������ ����Ǿ��ٴ� �÷��׸� ������
			this->notepannel->hasChanged = FALSE;
			//�������� ������ �����Ѵ�.
			CString windowTitle;
			windowTitle.Format("%s - Windows �޸���", this->notepannel->document->GetName().c_str());
			this->notepannel->notepad->SetWindowText(windowTitle);
		}

		//������Ʈ�� �Ѵ�(��ġ, ���� ��)
		//this->notepannel->hasChanged = TRUE;
		this->notepannel->documentUploaded = TRUE;
		this->notepannel->clientMoveCheck = TRUE;
		this->notepannel->Notify();
		//Ŭ���̾�Ʈ�� �����ϴ�.
		this->notepannel->Invalidate(TRUE);
		//ĳ���� ����Ѵ�.
		this->notepannel->caret->ShowCaret();
	}

#if 0
	//������ ������ �����Ѵ�. 
	delete this->notepannel->select;
	this->notepannel->select = new Select(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);
	//���õǾ��ٴ� ǥ�ø� �ø���. 
	this->notepannel->isSelected = FALSE;
#endif
}