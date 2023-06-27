//HomeKey.cpp
/*
* ���ϸ�Ī:HomeKey.cpp
* ���:ȨŰ�� Ŭ���������� ����
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#include "HomeKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "ClientLocation.h"
#include "Scroll.h"
#include "Select.h"

/*
* �Լ���Ī:HomeKey
* ���:������
*/
HomeKey::HomeKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~HomeKey
* ���:�Ҹ���
*/
HomeKey::~HomeKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void HomeKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;

	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	currentLine->First();

	//���� ��ġ�� ���Ѵ�. 
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