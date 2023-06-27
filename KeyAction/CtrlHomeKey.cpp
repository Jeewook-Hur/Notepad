//CtrlHomeKey.cpp
/*
* ���ϸ�Ī:CtrlHomeKey.cpp
* ���:��Ʈ�Ѱ� ȨŰ�� Ŭ���������� ����
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#include "CtrlHomeKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "ClientLocation.h"
#include "Scroll.h"
#include "Select.h"

/*
* �Լ���Ī:CtrlHomeKey
* ���:������
*/
CtrlHomeKey::CtrlHomeKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlHomeKey
* ���:�Ҹ���
*/
CtrlHomeKey::~CtrlHomeKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlHomeKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
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