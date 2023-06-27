//DeleteCommand.cpp
/*
* ���ϸ�Ī:DeleteCommand.cpp
* ���:DeleteŰ Ŀ���
* �ۼ���:������
* �ۼ�����:2022/11/21
*/
#include "DeleteCommand.h"
#include "Notepannel.h"
#include "Select.h"

#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"

#include "KeyAction.h"
#include "KeyActionCreator.h"

/*
* �Լ���Ī:DeleteCommand
* ���:������
*/
DeleteCommand::DeleteCommand(Notepannel* notepannel) : notepannel(notepannel) {
	SHORT ctrlKeyState = GetKeyState(VK_CONTROL);
	SHORT shiftKeyState = GetKeyState(VK_SHIFT);
	BOOL isSelected = this->notepannel->isSelected;
	Glyph* currentLine = NULL;
	Glyph* nextLine = NULL;
	Glyph* endLine = NULL;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long endLineOrder = -1;
	Long endCharIndex = -2;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long paperLength = 0;
	Long lineLength = -1;

	this->wasSelected = FALSE;;


	//���� ��ġ�� ���Ѵ�. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	//���� ��ġ�� ���� ��ġ�� �����Ѵ�.
	frontLineOrder = lineOrder;
	frontCharIndex = charIndex;

	//������ ���̿� ���� ���� ���̸� ���Ѵ�. 
	paperLength = this->notepannel->paper->GetLength();
	lineLength = currentLine->GetLength();

	if (lineOrder < paperLength - 1) {
		nextLine = this->notepannel->paper->GetAt(lineOrder + 1);
	}

	if (charIndex >= lineLength - 1 && lineOrder < paperLength - 1 && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) {
		//���� ��ġ�� �� ���̰� ���� ���� �� ���� �ƴϰ� ����ƮŰ�� ������ ��
		//���� ���� �� ���� �� ��ġ�� �����Ѵ�.
		endLineOrder = lineOrder + 1;
		endCharIndex = -1;
	}
	else if (charIndex < lineLength - 1 && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) { 
		//���� ��ġ�� �� ���� �ƴϰ� ����ƮŰ�� ������ ��
		endLineOrder = frontLineOrder;
		endCharIndex = frontCharIndex + 1;
	}
	else if (charIndex >= lineLength - 1 && lineOrder < paperLength - 1 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) { 
		//���� ��ġ�� �� ���̰� ���� ���� �� ���� �ƴϰ� ctrl+����ƮŰ�� ������ ��
		endLineOrder = lineOrder + 1;
		endLine = this->notepannel->paper->GetAt(endLineOrder);
		endLine->First();
		endCharIndex = endLine->NextWord();
	}
	else if (charIndex < lineLength - 1 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) { 
		//���� ��ġ�� �� ���� �ƴϰ� ctrl+����ƮŰ�� ������ ��
		endLineOrder = frontLineOrder;
		endCharIndex = currentLine->NextWord();
	}
	else if (charIndex >= lineLength - 1 && lineOrder < paperLength - 1 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000) && isSelected == FALSE) {
		//���� ��ġ�� �� ���̰� ���� ���� �� ���� �ƴϰ� ctrl+shift+delete Ű�� ������ ��
		endLineOrder = lineOrder + 1;
		endLine = this->notepannel->paper->GetAt(endLineOrder);
		endCharIndex = endLine->Last();
	}
	else if (charIndex < lineLength - 1 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000) && isSelected == FALSE) {
		//���� ��ġ�� �� ���� �ƴϰ� ctrl+shift+delete Ű�� ������ ��
		endLineOrder = frontLineOrder;
		endCharIndex = currentLine->Last();
	}
	else if (isSelected == TRUE) { //���õǾ��� �� ����ƮŰ�� ������ ��
		this->wasSelected = TRUE;
		frontLineOrder = this->notepannel->select->frontLineOrder;
		frontCharIndex = this->notepannel->select->frontXIndex;
		endLineOrder = this->notepannel->select->endLineOrder;
		endCharIndex = this->notepannel->select->endXIndex;
		
	}

	if (charIndex >= lineLength - 1 && lineOrder < paperLength - 1 && dynamic_cast<DummyLine*>(nextLine) && isSelected == FALSE) {
		endCharIndex++;
	}

	//���� ��ġ�� ���� ��ġ�� �����Ѵ�.
	this->notepannel->paper->GetLocation(frontLineOrder, frontCharIndex, &this->frontLineLocation, &this->frontCharLocation);
	this->notepannel->paper->GetLocation(endLineOrder, endCharIndex, &this->endLineLocation, &this->endCharLocation);

	//���� ��ġ�� �������� ���Ѵ�. 
	this->previousPaper = this->notepannel->paper->Clone(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);
	this->previousPaper->MergeAllDummyLines();
}

/*
* �Լ���Ī:~DeleteCommand
* ���:�Ҹ���
*/
DeleteCommand::~DeleteCommand() {
	delete this->previousPaper;
}

/*
* �Լ���Ī:Execute
* ���:Ŀ��带 �����ϴ�
*/
void DeleteCommand::Execute() {
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long endLineOrder = -1;
	Long endCharIndex = -2;
	
	//���̿� ����
	this->notepannel->paper->MergeAllDummyLines();

	//���� ��ġ�� ���� ��ġ�� ġȯ�Ѵ�.
	this->notepannel->paper->MoveToLocation(this->frontLineLocation, this->frontCharLocation, &frontLineOrder, &frontCharIndex);
	this->notepannel->paper->MoveToLocation(this->endLineLocation, this->endCharLocation, &endLineOrder, &endCharIndex);

	//���� ������ ������ �����. 
	this->notepannel->paper->Remove(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);

	//����Ŭ������ �ʱ�ȭ�Ѵ�.
	delete this->notepannel->select;
	this->notepannel->select = new Select(notepannel);

#if 0
	KeyActionCreator keyActionCreator(this->notepannel);
	KeyAction* keyAction = NULL;

	keyAction = keyActionCreator.Create(VK_DELETE, 0, 0);
	if (keyAction != NULL) {
		keyAction->OnKeyDown(VK_DELETE, 0, 0);
	}
	delete keyAction;
#endif
}

/*
* �Լ���Ī:UnExecute
* ���:Ŀ��带 ��������Ѵ�. 
*/
void DeleteCommand::UnExecute() {
	Glyph* currentLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long endLineOrder = -1;
	Long endCharIndex = -2;

	//���̿� ����
	this->notepannel->paper->MergeAllDummyLines();

	//���� ���� ��ġ�� ���� ��ġ�� ġȯ�Ѵ�.
	this->notepannel->paper->MoveToLocation(this->frontLineLocation, this->frontCharLocation, &frontLineOrder, &frontCharIndex);
	//���� ��ġ�� ����� ������ �����Ѵ�.
	this->notepannel->paper->Add(this->previousPaper, frontLineOrder, frontCharIndex);

	//���� ���� ��ġ�� ���� ��ġ�� ġȯ�Ѵ�.
	this->notepannel->paper->MoveToLocation(this->endLineLocation, this->endCharLocation, &endLineOrder, &endCharIndex);
	//������ ��ġ�� ������ �̵��Ѵ�. 
	lineOrder = this->notepannel->paper->Move(frontLineOrder);
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	currentLine->Move(frontCharIndex);

	if (this->wasSelected == TRUE) {
		//������ ��ġ�� �����Ѵ�. 
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);
	}
	else { //�������� �ʾҾ ����Ʈ�� �����������ش�.
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel);
	}
}