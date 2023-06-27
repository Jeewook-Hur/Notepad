//ShiftUpKey.cpp
/*
* ���ϸ�Ī:ShiftUpKey.cpp
* ���:shift�� ���� ȭ��ǥ�� Ŭ���������� ����
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#include "ShiftUpKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"

/*
* �Լ���Ī:ShiftUpKey
* ���:������
*/
ShiftUpKey::ShiftUpKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~ShiftUpKey
* ���:�Ҹ���
*/
ShiftUpKey::~ShiftUpKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void ShiftUpKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	int lineOrder = -1;
	int previousLineWidth = 0;
	int charIndex = -2;
	int clientLineOrder = this->notepannel->clientLocation->lineOrder;
	int lineNumberInPage = this->notepannel->clientMatrix->lineNumberInPage;
	int lineInClientEnd = clientLineOrder + lineNumberInPage;

	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	//���� ���� ���� ��ġ�� ���� ���Ѵ�.
	previousLineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine, charIndex);

	//���� ��ġ�� �°� �̵��Ѵ�.
	if (lineOrder >= clientLineOrder && lineOrder <= lineInClientEnd) { //���� ��ġ�� Ŭ���̾�Ʈ �ȿ� ������
		//�����ٷ� �̵��Ѵ�.
		lineOrder = this->notepannel->paper->Previous();
	}
	else if (lineOrder < clientLineOrder) { //���� ��ġ�� Ŭ���̾�Ʈ ���� ������
		//Ŭ���̾�Ʈ ��ġ �ٷ� ���� �̵��Ѵ�
		lineOrder = this->notepannel->paper->Move(clientLineOrder - 1);
	}
	else if (lineOrder > lineInClientEnd) { //���� ��ġ�� Ŭ���̾�Ʈ �Ʒ��� ������
		//Ŭ���̾�Ʈ ��ġ �ٷ� �Ʒ��� �̵��Ѵ�.
		lineOrder = this->notepannel->paper->Move(lineInClientEnd + 1);
	}

	//�����ȿ��� �����ٰ� ������ ��ġ�� �̵��Ѵ�.
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = this->notepannel->characterMatrix->FindNearWidthPosition(currentLine, previousLineWidth);
	currentLine->Move(charIndex);

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
	UpKey upKey(this->notepannel);
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
	upKey.OnKeyDown(0, 0, 0);
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
		this->notepannel->Invalidate(FALSE);
	}
	//ĳ���� ���̰��Ѵ�.
	this->notepannel->caret->ShowCaret();
#endif
}