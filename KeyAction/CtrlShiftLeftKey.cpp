//CtrlShiftLeftKey.cpp
/*
* ���ϸ�Ī:CtrlShiftLeftKey.cpp
* ���:shift�� ������ ȭ��ǥ�� Ŭ���������� ����
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#include "CtrlShiftLeftKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"
#include "DummyLine.h"

/*
* �Լ���Ī:CtrlShiftLeftKey
* ���:������
*/
CtrlShiftLeftKey::CtrlShiftLeftKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlShiftLeftKey
* ���:�Ҹ���
*/
CtrlShiftLeftKey::~CtrlShiftLeftKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlShiftLeftKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Long charIndex = -2;
	Long lineOrder = -1;
	Long order = -2;

	Long charIndexMoved = -2;
	Glyph* clonePaper = 0;
	Glyph* previousLineMerged = 0;
	Long previousLineLength = -1;

	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);

	charIndex = currentLine->GetCurrent();
	if (charIndex > -1) {
		charIndexMoved = currentLine->PreviousWord();
		if (charIndexMoved <= -1 && lineOrder > 0 && dynamic_cast<DummyLine*>(currentLine)) {
			clonePaper = this->notepannel->paper->Clone(lineOrder - 1, -1, lineOrder, charIndex);
			clonePaper->MergeAllDummyLines();
			previousLineLength = this->notepannel->paper->GetAt(lineOrder - 1)->GetLength();
			previousLineMerged = clonePaper->GetAt(0);
			previousLineMerged->Last();
			charIndexMoved = previousLineMerged->PreviousWord();
			if (charIndexMoved < previousLineLength - 1) {
				lineOrder = this->notepannel->paper->Previous();
				currentLine = this->notepannel->paper->GetAt(lineOrder);
				currentLine->Move(charIndexMoved);
			}
			delete clonePaper;
		}
	}
	else if (charIndex <= -1 && lineOrder > 0 && !dynamic_cast<DummyLine*>(currentLine)) {
		lineOrder = this->notepannel->paper->Previous();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		currentLine->Move(currentLine->GetLength() - 1);
	}
	else if (charIndex <= -1 && lineOrder > 0 && dynamic_cast<DummyLine*>(currentLine)) {
		lineOrder = this->notepannel->paper->Previous();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		currentLine->Move(currentLine->GetLength() - 1);
		currentLine->PreviousWord();
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
	CtrlLeftKey ctrlLeftKey(this->notepannel);
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
	ctrlLeftKey.OnKeyDown(0, 0, 0);
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