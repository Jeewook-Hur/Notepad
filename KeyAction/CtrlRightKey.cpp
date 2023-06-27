//CtrlRightKey.cpp
/*
* ���ϸ�Ī:CtrlRightKey.cpp
* ���:��Ʈ�Ѱ� ������ ȭ��ǥ�� Ŭ���������� ����
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#include "CtrlRightKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"
#include "DummyLine.h"

/*
* �Լ���Ī:CtrlRightKey
* ���:������
*/
CtrlRightKey::CtrlRightKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlRightKey
* ���:�Ҹ���
*/
CtrlRightKey::~CtrlRightKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlRightKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
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