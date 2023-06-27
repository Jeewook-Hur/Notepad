//SelectDelete.cpp
/*
* ���ϸ�Ī:SelectDelete.cpp
* ���:���ÿ����� ���ﶧ�� ����
* �ۼ���:������
* �ۼ�����:2022/11/15
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
* �Լ���Ī:SelectDelete
* ���:������
*/
SelectDelete::SelectDelete(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~SelectDelete
* ���:�Ҹ���
*/
SelectDelete::~SelectDelete() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void SelectDelete::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* frontLine = NULL;
	Glyph* endLine = NULL;
	int frontLineOrder = this->notepannel->select->frontLineOrder;
	int endLineOrder = this->notepannel->select->endLineOrder;
	int frontCharIndex = this->notepannel->select->frontXIndex;
	int endCharIndex = this->notepannel->select->endXIndex;
	int frontLength;
	//�� ������ �����´�.
	frontLine = this->notepannel->paper->GetAt(frontLineOrder);

	if (!(frontLineOrder == endLineOrder && frontCharIndex == endCharIndex)) {//���õ� ������ ������
		if (frontLineOrder == endLineOrder) {//�Ǿ��ٰ� �ǵ� ���� ������ �ش� ���� �Ǿպ��� ������ �����.
			frontLine->Remove(frontCharIndex + 1, endCharIndex);
		}
		else {//�Ǿհ� �ǵ� ���� �ٸ���
			//�Ǿ� �ٿ��� ���õ� �κк��� ������ �����.
			frontLength = frontLine->GetLength();
			frontLine->Remove(frontCharIndex + 1, frontLength - 1);
			//���� ���� �����´�.
			endLine = this->notepannel->paper->GetAt(endLineOrder);
			//���� �ٿ��� �� �պ��� ���õ� �κб��� �����.
			endLine->Remove(0, endCharIndex);
			//�� �� ���� ���� ���� ���� ��ģ��.
			frontLine->Add(endLine, frontCharIndex + 1);
			//������ ���� �ٺ��� ������ �ٱ��� �����.
			this->notepannel->paper->Remove(frontLineOrder + 1, endLineOrder);
		}
		//���� ��ġ�� �� �� ��ġ�� �̵��Ѵ�.
		frontLineOrder = this->notepannel->paper->Move(frontLineOrder);
		frontLine = this->notepannel->paper->GetAt(frontLineOrder);
		frontLine->Move(frontCharIndex);
		//���ÿ����� �ʱ�ȭ�Ѵ�.
		delete this->notepannel->select;
		this->notepannel->select = new Select(notepannel);
		//���õǾ��ٴ� ǥ�ø� ������. 
		this->notepannel->isSelected = FALSE;

		//������ ����Ǿ����� ǥ���Ѵ�. 
		this->notepannel->hasChanged = TRUE;
		//�������� ������ �����Ѵ�.
		CString windowTitle;
		windowTitle.Format("*%s - Windows �޸���", this->notepannel->document->GetName().c_str());
		this->notepannel->notepad->SetWindowText(windowTitle);

		this->notepannel->documentUploaded = TRUE;
		this->notepannel->clientMoveCheck = TRUE;
		this->notepannel->Notify();
		this->notepannel->Invalidate(TRUE);
		this->notepannel->caret->ShowCaret();
	}
}