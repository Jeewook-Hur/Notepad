//BackspaceKey.cpp
/*
* ���ϸ�Ī:BackspaceKey.cpp
* ���:�齺���̽�Ű�� ���������� �̺�Ʈ
* �ۼ���:������
* �ۼ�����:2022/9/16
*/
#include "BackspaceKey.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "resource.h"
#include "CommandCreator.h"
#include "Command.h"
#include "MacroCommand.h"
#include "Document.h"

/*
* �Լ���Ī:BackspaceKey
* ���:������
*/
BackspaceKey::BackspaceKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~BackspaceKey
* ���:�Ҹ���
*/
BackspaceKey::~BackspaceKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void BackspaceKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {	
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	Glyph* currentLine = NULL;
	Glyph* tempLine = NULL;
	Glyph* character = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long tempOrder = -2;
	Long tempLength = -1;
	Long order = 0;
	Long i = 0;
	UINT lineWrapState = -1;


	command = commandCreator.Create(VK_BACK, 0, 0);
	if (command != NULL) {
		command->Execute();
		this->notepannel->macroCommand->Add(command, 1);
	}

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

#if 0
	//���̿��� ���� ���� ��ġ�� ã�´�.
	lineOrder = this->notepannel->paper->GetCurrent();
	//���̿��� ���� ���� �����´�.
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	//���� �ٿ��� ���� �ܾ� ��ġ�� �����´�.
	charIndex = currentLine->GetCurrent();
	if (charIndex > -1) {//���� �ܾ� ��ġ�� �� ó���� �ƴϸ�
		//�ܾ� ��ġ ���� ������ �ܾ �����.
		currentLine->Remove(charIndex);
	}
	else if (charIndex <= -1 && lineOrder > 0) {//���� �ܾ� ��ġ�� �� ó���̰� ���� ���� �� ó���� �ƴϸ�
		//���� ���� ����Ѵ�.
		tempLine = currentLine->Clone();
		//���� ���� �����.
		this->notepannel->paper->Remove(lineOrder);
		//�ٲ� ���� ���� �����´�.
		lineOrder = this->notepannel->paper->GetCurrent();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		//���� ���� �ǵڷ� �̵��Ѵ�.
		//���� ���� ��ġ�� ����Ѵ�.
		tempOrder = currentLine->Last();

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
		if (lineWrapState == MF_CHECKED && tempOrder > -1) { //�ڵ��������� �����ְ� ��ģ���� �Ǿ��� �ƴϸ�
			//�ѱ��� �� �����. 
			currentLine->Remove(tempOrder);
		}
	}

	//������ ����Ǿ����� ǥ���Ѵ�. 
	this->notepannel->documentUploaded = TRUE;
	//Ŭ���̾�Ʈ�� �ڵ��̵��� �ʿ����� üũ�Ѵ�. 
	this->notepannel->clientMoveCheck = TRUE;
	//������Ʈ ���� �Լ��� ȣ���Ѵ�.
	this->notepannel->Notify();
#endif
}