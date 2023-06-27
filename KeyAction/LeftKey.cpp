//LeftKey.cpp
/*
* ���ϸ�Ī:LeftKey.cpp
* ���:���� ȭ��ǥ�� Ŭ���������� ����
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#include "LeftKey.h"
#include "Notepannel.h"
#include "Caret.h"
#include "CharacterMatrix.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"

#include "DummyLine.h"

/*
* �Լ���Ī:LeftKey
* ���:������
*/
LeftKey::LeftKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~LeftKey
* ���:�Ҹ���
*/
LeftKey::~LeftKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void LeftKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Long charIndex = -2;
	Long lineOrder = -1;
	Long order = -2;


	if (this->notepannel->isSelected == FALSE) {//���õǾ��ٴ� ǥ�ð� ������ ������
		lineOrder = this->notepannel->paper->GetCurrent();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		charIndex = currentLine->GetCurrent();
		if (charIndex > -1) {
			currentLine->Previous();
		}
		else if (charIndex <= -1 && lineOrder > 0 && !dynamic_cast<DummyLine*>(currentLine)) {
			lineOrder = this->notepannel->paper->Previous();
			currentLine = this->notepannel->paper->GetAt(lineOrder);
			currentLine->Move(currentLine->GetLength() - 1);
		}
		else if (charIndex <= -1 && lineOrder > 0 && dynamic_cast<DummyLine*>(currentLine)) {
			lineOrder = this->notepannel->paper->Previous();
			currentLine = this->notepannel->paper->GetAt(lineOrder);
			currentLine->Move(currentLine->GetLength() - 2);
		}

		//������Ʈ ���� �Լ��� ȣ���Ѵ�.
		this->notepannel->clientMoveCheck = TRUE;
		this->notepannel->Notify();
	}
	else { //���õǾ��ٴ� ǥ�ð� �ö� ������
		//���õǾ��ٴ� �÷��׸� ������.
		this->notepannel->isSelected = FALSE;
		//������ġ�� �����ϱ��� �� ��ġ�� �����Ѵ�.
		lineOrder = this->notepannel->paper->Move(this->notepannel->select->frontLineOrder);
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		charIndex = currentLine->Move(this->notepannel->select->frontXIndex);
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