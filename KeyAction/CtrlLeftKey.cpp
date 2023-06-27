//CtrlLeftKey.cpp
/*
* ���ϸ�Ī:CtrlLeftKey.cpp
* ���:��Ʈ�Ѱ� ���� ȭ��ǥ�� Ŭ���������� ����
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#include "CtrlLeftKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"

#include "DummyLine.h"


/*
* �Լ���Ī:CtrlLeftKey
* ���:������
*/
CtrlLeftKey::CtrlLeftKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlLeftKey
* ���:�Ҹ���
*/
CtrlLeftKey::~CtrlLeftKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlLeftKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
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