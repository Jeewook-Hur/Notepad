//DownKey.cpp
/*
* ���ϸ�Ī:DownKey.cpp
* ���:�Ʒ� ȭ��ǥ�� Ŭ���������� ����
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#include "DownKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"

/*
* �Լ���Ī:DownKey
* ���:������
*/
DownKey::DownKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~DownKey
* ���:�Ҹ���
*/
DownKey::~DownKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void DownKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
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
		lineOrder = this->notepannel->paper->Next();
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