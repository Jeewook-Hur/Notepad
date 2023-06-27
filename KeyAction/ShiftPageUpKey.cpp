//ShiftPageUpKey.cpp
/*
* ���ϸ�Ī:ShiftPageUpKey.cpp
* ���:shift�� ��������Ű�� Ŭ���������� ����
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#include "ShiftPageUpKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "ClientMatrix.h"
#include "ClientLocation.h"
#include "Scroll.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"

/*
* �Լ���Ī:ShiftPageUpKey
* ���:������
*/
ShiftPageUpKey::ShiftPageUpKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~ShiftPageUpKey
* ���:�Ҹ���
*/
ShiftPageUpKey::~ShiftPageUpKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void ShiftPageUpKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	int lineOrder;
	int charIndex;
	int previousLineWidth;
	int lineNumberInPage = this->notepannel->clientMatrix->lineNumberInPage;
	int clientLineOrder = this->notepannel->clientLocation->lineOrder;

	//���� ���� ��ġ�� �д´�.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//���� �ٿ��� ������ġ�� ���� ���Ѵ�.
	previousLineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine, charIndex);
	//�� �������� �̵��Ѵ�.
	if (lineOrder < lineNumberInPage * 2 - 1) { //���� ��ġ�� �� ó�� �������� ��ġ�� ������
		//���� ��ġ�� Ŭ���̾�Ʈ������ ��ġ�� ������ ��ġ�̴�.
		lineOrder = lineOrder - clientLineOrder;
		clientLineOrder = 0;
	}
	else { //���� ��ġ�� �� ó�� �������� �ƴϸ� 
		//�� ������ ���� �̵��Ѵ�.
		lineOrder = lineOrder - lineNumberInPage;
		clientLineOrder = clientLineOrder - lineNumberInPage;
	}
	lineOrder = this->notepannel->paper->Move(lineOrder);
	//�̵��� �ٿ��� �������� ���� ����� ��ġ�� ã�� �̵��Ѵ�. 
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = this->notepannel->characterMatrix->FindNearWidthPosition(currentLine, previousLineWidth);
	charIndex = currentLine->Move(charIndex);
	//Ŭ���̾�Ʈ�� ���η� �̵��Ѵ�.
	this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, clientLineOrder);
	this->notepannel->scroll->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);

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
	PageUpKey pageUpKey(this->notepannel);
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
	pageUpKey.OnKeyDown(0, 0, 0);
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