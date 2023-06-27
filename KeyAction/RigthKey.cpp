//RightKey.cpp
/*
* ���ϸ�Ī:RightKey.cpp
* ���:������ ȭ��ǥ�� Ŭ���������� ����
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#include "RightKey.h"
#include "Notepannel.h"
#include "Caret.h"
#include "CharacterMatrix.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"
#include "DummyLine.h"

/*
* �Լ���Ī:RightKey
* ���:������
*/
RightKey::RightKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~RightKey
* ���:�Ҹ���
*/
RightKey::~RightKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void RightKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Long charIndex = -2;
	Long lineOrder = -1;
	Long order = -2;

	Glyph* nextLine = 0;
	
	if (this->notepannel->isSelected == FALSE) {//���õǾ��ٴ� ǥ�ð� ������ ������
		lineOrder = this->notepannel->paper->GetCurrent();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		charIndex = currentLine->GetCurrent();

		if (lineOrder < this->notepannel->paper->GetLength() - 1) {
			nextLine = this->notepannel->paper->GetAt(lineOrder + 1);
		}

		if (charIndex < currentLine->GetLength() - 1) {
			currentLine->Next();
		}
		else if (charIndex >= currentLine->GetLength() - 1 && lineOrder < this->notepannel->paper->GetLength() - 1 && !dynamic_cast<DummyLine*>(nextLine)) {
			lineOrder = this->notepannel->paper->Next();
			currentLine = this->notepannel->paper->GetAt(lineOrder);
			currentLine->Move(-1);
		}
		else if (charIndex >= currentLine->GetLength() - 1 && lineOrder < this->notepannel->paper->GetLength() - 1 && dynamic_cast<DummyLine*>(nextLine)) {
			lineOrder = this->notepannel->paper->Next();
			currentLine = this->notepannel->paper->GetAt(lineOrder);
			currentLine->Move(0);
		}
		//������Ʈ ���� �Լ��� ȣ���Ѵ�.
		//ĳ���� ������Ʈ �Ѵ�. 
		this->notepannel->clientMoveCheck = TRUE;
		this->notepannel->Notify();
	}
	if (this->notepannel->isSelected == TRUE) { //���õǾ��ٴ� ǥ�ð� �ö� ������
		//���õǾ��ٴ� �÷��׸� ������.
		this->notepannel->isSelected = FALSE;
		//������ġ�� �����ϱ��� �� ��ġ�� �����Ѵ�.
		lineOrder = this->notepannel->paper->Move(this->notepannel->select->endLineOrder);
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		charIndex = currentLine->Move(this->notepannel->select->endXIndex);
		//������Ʈ ���� �Լ��� ȣ���Ѵ�.
		this->notepannel->clientMoveCheck = TRUE;
		this->notepannel->Notify();
		//Ŭ���̾�Ʈ ���� �Լ��� ȣ���Ѵ�.
		this->notepannel->Invalidate(TRUE);
	}

	//���� ��ġ�� ���Ѵ�. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//���� ��ġ�� ���� Ŭ������ �ʱ�ȭ�Ѵ�. 
	delete this->notepannel->select;
	this->notepannel->select = new Select(this->notepannel, charIndex, lineOrder, charIndex, lineOrder);
	//������Ʈ ���� �Լ��� ȣ���Ѵ�.
	//ĳ���� ������Ʈ �Ѵ�. 
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//Ŭ���̾�Ʈ ���� �Լ��� ȣ���Ѵ�.
	this->notepannel->Invalidate(TRUE);
	//ĳ���� ���̰��Ѵ�.
	this->notepannel->caret->ShowCaret();
}