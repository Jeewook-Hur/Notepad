//DeleteKey.cpp
/*
* ���ϸ�Ī:DeleteKey.cpp
* ���:����ƮŰ�� ���������� �̺�Ʈ
* �ۼ���:������
* �ۼ�����:2022/9/16
*/
#include "DeleteKey.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "CommandCreator.h"
#include "Command.h"
#include "MacroCommand.h"
#include "resource.h"


#include "CharacterMatrix.h"
#include "Caret.h"
#include "DocumentVirtualSize.h"
#include "Paper.h"
#include "Line.h"
#include "Document.h"

/*
* �Լ���Ī:DeleteKey
* ���:������
*/
DeleteKey::DeleteKey(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~DeleteKey
* ���:�Ҹ���
*/
DeleteKey::~DeleteKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void DeleteKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;

	Glyph* currentLine = 0;
	Long lineOrder;
	Long charIndex;
	Long lineLength;
	Long paperLength;

	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	paperLength = this->notepannel->paper->GetLength();
	lineLength = currentLine->GetLength();

	
	if (!(lineOrder >= paperLength - 1 && charIndex >= lineLength - 1) || this->notepannel->isSelected == TRUE) {
		command = commandCreator.Create(IDM_FORMAT_DELETE);
		if (command != NULL) {
			command->Execute();
			this->notepannel->macroCommand->Add(command, 1);
		}
	}
	

#if 0
	Glyph* currentLine = NULL;
	Glyph* tempLine = NULL;
	Glyph* character = NULL;
	Long paperLength = 0;
	Long lineOrder = -1;
	Long lineLength = -1;
	Long charIndex = -2;
	Long tempOrder = -2;
	Long tempLength = -1;
	Long order = 0;
	Long i = 0;
	UINT lineWrapState = -1;

	paperLength = this->notepannel->paper->GetLength();
	//���̿��� ���� ���� ��ġ�� ã�´�.
	lineOrder = this->notepannel->paper->GetCurrent();
	//���̿��� ���� ���� �����´�.
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	//���� �ٿ��� ���� �ܾ� ��ġ�� �����´�.
	charIndex = currentLine->GetCurrent();
	lineLength = currentLine->GetLength();
	if (charIndex < lineLength - 1) {//���� ��ġ�� �� ���� �ƴϸ�
		//�ܾ� ��ġ ���� ������ �ܾ �����. 
		currentLine->Remove(charIndex + 1);
	}
	else if (charIndex >= lineLength - 1 && lineOrder < paperLength - 1) {//���� ��ġ�� �� ���̰� ���� ���� �� ���� �ƴϸ�
		//���� ���� ����Ѵ�. 
		tempLine = this->notepannel->paper->GetAt(lineOrder + 1)->Clone();
		//���� ���� �����.
		this->notepannel->paper->Remove(lineOrder + 1);
		this->notepannel->paper->Move(lineOrder);
		//���� ���� ���� �ܾ� ��ġ�� ����Ѵ�. 
		tempOrder = currentLine->GetCurrent();
		//����� ���� ���̸�ŭ �ݺ��Ѵ�. 
		tempLength = tempLine->GetLength();
		while (i < tempLength) {//����� ���� ���̸�ŭ �ݺ��Ѵ�.
			//�ٿ� ����� ���� ������ ���纻�� �ٿ�����.
			character = tempLine->GetAt(order);
			order++;
			currentLine->Add(character->Clone());
			i++;
		}

		//�ٿ��� ����� �ܾ���ġ�� �̵��Ѵ�.
		currentLine->Move(tempOrder);
		//����� ���� �����Ѵ�.
		delete tempLine;

		lineWrapState = this->notepannel->cMenu.GetMenuState(IDM_FORMAT_LINEWRAP, MF_BYCOMMAND);
		if (lineWrapState == MF_CHECKED && tempOrder < currentLine->GetLength() - 1) { //�ڵ��������� �����ְ� ��ģ���� ���� �ƴϸ�
			//�ѱ��� �� �����. 
			currentLine->Remove(tempOrder + 1);
		}
	}
#endif

	int charNumber = this->notepannel->paper->GetCharNumber();


	if (this->notepannel->macroCommand->savePoint == 0 && charNumber > 0) {
		//������ ����Ǿ����� ǥ���Ѵ�. 
		this->notepannel->hasChanged = TRUE;

		//�������� ������ �����Ѵ�.
		CString windowTitle;
		windowTitle.Format("*%s - Windows �޸���", this->notepannel->document->GetName().c_str());
		this->notepannel->notepad->SetWindowText(windowTitle);
	}
	else if (this->notepannel->macroCommand->savePoint == 0 && charNumber <= 0) {
		this->notepannel->hasChanged = FALSE;
		//�������� ������ �����Ѵ�.
		CString windowTitle;
		windowTitle.Format("%s - Windows �޸���", this->notepannel->document->GetName().c_str());
		this->notepannel->notepad->SetWindowText(windowTitle);
	}

	this->notepannel->documentUploaded = TRUE;
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//deleteŰ�� ��� ȣ���� ���ϱ⿡ ȣ���Լ��� �ʿ��ϴ�. 
	this->notepannel->Invalidate(TRUE);
	//ĳ���� ���̰��Ѵ�.
	this->notepannel->caret->ShowCaret();
}
