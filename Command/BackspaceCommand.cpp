//BackspaceCommand.cpp
/*
* ���ϸ�Ī:BackspaceCommand.cpp
* ���:�齺���̽� Ŀ���
* �ۼ���:������
* �ۼ�����:2022/12/2
*/
#include "BackspaceCommand.h"
#include "Notepannel.h"
#include "Select.h"

#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"

#include "KeyAction.h"
#include "KeyActionCreator.h"

/*
* �Լ���Ī:BackspaceCommand
* ���:������
*/
BackspaceCommand::BackspaceCommand(Notepannel* notepannel, UINT nChar, UINT nRepCnt, UINT nFlags) : notepannel(notepannel) {
	SHORT ctrlKeyState = GetKeyState(VK_CONTROL);
	SHORT shiftKeyState = GetKeyState(VK_SHIFT);
	BOOL isSelected = this->notepannel->isSelected;
	Glyph* currentLine = NULL;
	Glyph* frontLine = NULL;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long endLineOrder = -1;
	Long endCharIndex = -2;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long lineLength = -1;

	this->wasSelected = FALSE;;

	//���� ��ġ�� ���Ѵ�. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	//���� ��ġ�� ������ ��ġ�� �����Ѵ�.
	endLineOrder = lineOrder;
	endCharIndex = charIndex;

	if (charIndex <= -1 && lineOrder > 0 && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) {
		//���� ��ġ�� �� ���̰� ���� ���� �� ���� �ƴϰ� �齺���̽�Ű�� ������ ��
		//���� ���� �� �ڸ� �� ��ġ�� �����Ѵ�.
		frontLineOrder = lineOrder - 1;
		frontLine = this->notepannel->paper->GetAt(frontLineOrder);
		frontCharIndex = frontLine->Last();
	}
	else if (charIndex > -1 && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) {
		//���� ��ġ�� �� ���� �ƴϰ� �齺���̽�Ű�� ������ ��
		frontLineOrder = endLineOrder;
		frontCharIndex = endCharIndex - 1;
	}
	else if (charIndex <= -1 && lineOrder > 0 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) {
		//���� ��ġ�� �� ���̰� ���� ���� �� ���� �ƴϰ� ctrl+�齺���̽�Ű�� ������ ��
		frontLineOrder = lineOrder - 1;
		frontLine = this->notepannel->paper->GetAt(frontLineOrder);
		frontLine->Last();
		frontCharIndex = frontLine->PreviousWord();
	}
	else if (charIndex > -1 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) {
		//���� ��ġ�� �� ���� �ƴϰ� ctrl+�齺���̽�Ű�� ������ ��
		frontLineOrder = endLineOrder;
		frontCharIndex = currentLine->PreviousWord();
	}
	else if (charIndex <= -1 && lineOrder > 0 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000) && isSelected == FALSE) {
		//���� ��ġ�� �� ���̰� ���� ���� �� ���� �ƴϰ� ctrl+shift+backspace Ű�� ������ ��
		frontLineOrder = lineOrder - 1;
		frontLine = this->notepannel->paper->GetAt(endLineOrder);
		frontCharIndex = frontLine->First();
	}
	else if (charIndex > -1 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000) && isSelected == FALSE) {
		//���� ��ġ�� �� ���� �ƴϰ� ctrl+shift+backspace Ű�� ������ ��
		frontLineOrder = endLineOrder;
		frontCharIndex = currentLine->First();
	}
	else if (isSelected == TRUE) { //���õǾ��� �� �齺���̽�Ű�� ������ ��
		this->wasSelected = TRUE;
		frontLineOrder = this->notepannel->select->frontLineOrder;
		frontCharIndex = this->notepannel->select->frontXIndex;
		endLineOrder = this->notepannel->select->endLineOrder;
		endCharIndex = this->notepannel->select->endXIndex;
	}

	if (dynamic_cast<DummyLine*>(currentLine) && charIndex <= -1 && lineOrder > 0 && isSelected == FALSE) {
		frontCharIndex--;
	}

	//���� ��ġ�� ���� ��ġ�� �����Ѵ�.
	this->notepannel->paper->GetLocation(endLineOrder, endCharIndex, &this->endLineLocation, &this->endCharLocation);
	this->notepannel->paper->GetLocation(frontLineOrder, frontCharIndex, &this->frontLineLocation, &this->frontCharLocation);

	//���� ��ġ�� �������� ���Ѵ�. 
	this->previousPaper = this->notepannel->paper->Clone(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);
	this->previousPaper->MergeAllDummyLines();
}

/*
* �Լ���Ī:~BackspaceCommand
* ���:�Ҹ���
*/
BackspaceCommand::~BackspaceCommand() {
	delete this->previousPaper;
}

/*
* �Լ���Ī:Execute
* ���:Ŀ��带 �����ϴ�
*/
void BackspaceCommand::Execute() {
	Glyph* currentLine = 0;
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

	//���� ��ġ�� �̵��Ѵ�.
	this->notepannel->paper->Move(frontLineOrder);
	this->notepannel->paper->GetAt(frontLineOrder)->Move(frontCharIndex);

	//����Ŭ������ �ʱ�ȭ�Ѵ�.
	delete this->notepannel->select;
	this->notepannel->select = new Select(notepannel);

}

/*
* �Լ���Ī:UnExecute
* ���:Ŀ��带 ��������Ѵ�.
*/
void BackspaceCommand::UnExecute() {
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
	lineOrder = this->notepannel->paper->Move(endLineOrder);
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	currentLine->Move(endCharIndex);
	
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