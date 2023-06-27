//CtrlShiftRightKey.cpp
/*
* ���ϸ�Ī:CtrlShiftRightKey.cpp
* ���:shift�� ������ ȭ��ǥ�� Ŭ���������� ����
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#include "CtrlShiftRightKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"
#include "DummyLine.h"

/*
* �Լ���Ī:CtrlShiftRightKey
* ���:������
*/
CtrlShiftRightKey::CtrlShiftRightKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlShiftRightKey
* ���:�Ҹ���
*/
CtrlShiftRightKey::~CtrlShiftRightKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlShiftRightKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Long charIndex = -2;
	Long lineOrder = -1;
	Long order = -2;

	Glyph* nextLine = 0;
	Long nextLineLastIndex = -1;

	Long charIndexMoved = -2;
	Glyph* clonePaper = 0;
	Glyph* lineMerged = 0;
	Long currentLineLastIndex = -1;

	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	if (lineOrder < this->notepannel->paper->GetLength() - 1) {
		nextLine = this->notepannel->paper->GetAt(lineOrder + 1);
		nextLineLastIndex = nextLine->Last();
	}

	if (charIndex < currentLine->GetLength() - 1) {
		charIndexMoved = currentLine->NextWord();

		if (charIndexMoved >= currentLine->GetLength() - 1 && lineOrder < this->notepannel->paper->GetLength() - 1 && dynamic_cast<DummyLine*>(nextLine)) {
			currentLineLastIndex = currentLine->GetLength() - 1;
			clonePaper = this->notepannel->paper->Clone(lineOrder, -1, lineOrder + 1, nextLineLastIndex);
			clonePaper->MergeAllDummyLines();
			lineMerged = clonePaper->GetAt(0);
			lineMerged->Move(currentLineLastIndex);
			lineMerged->PreviousWord();
			charIndexMoved = lineMerged->NextWord();
			if (charIndexMoved > currentLineLastIndex) {
				lineOrder = this->notepannel->paper->Next();
				currentLine = this->notepannel->paper->GetAt(lineOrder);
				currentLine->First();
				currentLine->NextWord();
			}
			delete clonePaper;
		}
	}
	else if (charIndex >= currentLine->GetLength() - 1 && lineOrder < this->notepannel->paper->GetLength() - 1 && !dynamic_cast<DummyLine*>(nextLine)) {
		lineOrder = this->notepannel->paper->Next();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		currentLine->Move(-1);
	}
	else if (charIndex >= currentLine->GetLength() - 1 && lineOrder < this->notepannel->paper->GetLength() - 1 && dynamic_cast<DummyLine*>(nextLine)) {
		lineOrder = this->notepannel->paper->Next();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		currentLine->Move(-1);
		currentLine->NextWord();
	}
	//���� ��ġ�� ���Ѵ�. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//���� ��ġ�� ���� ������ �̵��Ѵ�.
	this->notepannel->select->MoveCurrent(charIndex, lineOrder);
	//������Ʈ ���� �Լ��� ȣ���Ѵ�.
	//ĳ���� ������Ʈ �Ѵ�. 
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//Ŭ���̾�Ʈ ���� �Լ��� ȣ���Ѵ�.
	this->notepannel->Invalidate(TRUE);
	//ĳ���� ���̰��Ѵ�.
	this->notepannel->caret->ShowCaret();

#if 0
	CtrlRightKey ctrlRightKey(this->notepannel);
	Glyph* currentLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long previousLineOrder = -1;
	Long previousCharIndex = -2;

	//�̵��ϱ� �� ��ġ�� ����Ѵ�.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	previousLineOrder = lineOrder;
	previousCharIndex = charIndex;

	//���õǾ��ٴ� �÷��׸� ������.
	this->notepannel->isSelected = FALSE;
	//�����ϱ� ����� ���� �ȵ� ����Ű�� ����� �����Ѵ�.
	ctrlRightKey.OnKeyDown(0, 0, 0);
	//���õǾ��ٴ� �÷��׸� �ø���.
	this->notepannel->isSelected = TRUE;
	//�̵� �� ��ġ�� Ȯ���Ѵ�.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//�̵��� ��ġ�� ���� ��ġ�� �ٸ���
	if (this->notepannel->paper->IsNotEqual(previousLineOrder, previousCharIndex)) {
		//�̵��� ��ġ�� �����ϱ⿡ �����Ѵ�.
		this->notepannel->select->MoveCurrent(charIndex, lineOrder);
		//Ŭ���̾�Ʈ ���� �Լ��� ȣ���Ѵ�.
		this->notepannel->Invalidate(TRUE);
	}
	//ĳ���� ���̰��Ѵ�.
	this->notepannel->caret->ShowCaret();
#endif
}