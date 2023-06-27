//CtrlShiftHomeKey.cpp
/*
* ���ϸ�Ī:CtrlShiftHomeKey.cpp
* ���:ctrlŰ�� shiftŰ�� ȨŰ�� Ŭ���������� ����
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#include "CtrlShiftHomeKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "ClientLocation.h"
#include "Scroll.h"
#include "Select.h"

/*
* �Լ���Ī:CtrlShiftHomeKey
* ���:������
*/
CtrlShiftHomeKey::CtrlShiftHomeKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlShiftHomeKey
* ���:�Ҹ���
*/
CtrlShiftHomeKey::~CtrlShiftHomeKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlShiftHomeKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;

	//�� ������ �̵��Ѵ�.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);

	lineOrder = this->notepannel->paper->First();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	currentLine->First();

	//���� ��ġ�� ���Ѵ�. 
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
	CtrlHomeKey ctrlHomeKey(this->notepannel);
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
	ctrlHomeKey.OnKeyDown(0, 0, 0);
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