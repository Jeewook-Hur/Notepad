//PageDownKey.cpp
/*
* ���ϸ�Ī:PageDownKey.cpp
* ���:������ �� Ű�� ���������� �̺�Ʈ�� �����ϴ� Ŭ����
* �ۼ���:������
* �ۼ�����:2022/10/5
*/
#include "PageDownKey.h"
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
* �Լ���Ī:PageDownKey
* ���:������
*/
PageDownKey::PageDownKey(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~PageDownKey
* ���:�Ҹ���
*/
PageDownKey::~PageDownKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void PageDownKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
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