//ShiftPageDownKey.cpp
/*
* ���ϸ�Ī:ShiftPageDownKey.cpp
* ���:shift�� PgDnŰ�� Ŭ���������� ����
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#include "ShiftPageDownKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "ClientMatrix.h"
#include "ClientLocation.h"
#include "DocumentVirtualSize.h"
#include "Scroll.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"

/*
* �Լ���Ī:ShiftPageDownKey
* ���:������
*/
ShiftPageDownKey::ShiftPageDownKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~ShiftPageDownKey
* ���:�Ҹ���
*/
ShiftPageDownKey::~ShiftPageDownKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void ShiftPageDownKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	int lineOrder;
	int charIndex;
	int previousLineWidth;
	int lineNumberInPage = this->notepannel->clientMatrix->lineNumberInPage;
	int clientLineOrder = this->notepannel->clientLocation->lineOrder;
	int availavableLineOrder = this->notepannel->documentVirtualSize->availableLine - 1;

	//���� ���� ��ġ�� �д´�.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//���� �ٿ��� ������ġ�� ���� ���Ѵ�.
	previousLineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine, charIndex);
	//�Ʒ� �������� �̵��Ѵ�.
	if (lineOrder > availavableLineOrder - lineNumberInPage) { //���� ��ġ�� ������ �������� ��ġ�� ������
		//���� ��ġ�� Ŭ���̾�Ʈ������ ��ġ�� ������ ��ġ�̴�.
		lineOrder = (lineOrder - clientLineOrder) + availavableLineOrder;
		clientLineOrder = availavableLineOrder;
	}
	else { //���� ��ġ�� �� ó�� �������� �ƴϸ� 
		//�� ������ ���� �̵��Ѵ�.
		lineOrder = lineOrder + lineNumberInPage;
		clientLineOrder = clientLineOrder + lineNumberInPage;
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
	PageDownKey pageDownKey(this->notepannel);
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
	pageDownKey.OnKeyDown(0, 0, 0);
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