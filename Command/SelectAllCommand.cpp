//SelectAllCommand.cpp
/*
* ���ϸ�Ī:SelectAllCommand.cpp
* ���:��ü�����ϴ� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#include "SelectAllCommand.h"
#include "Notepannel.h"
#include "Caret.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"

/*
* �Լ���Ī:SelectAllCommand
* ���:������
*/
SelectAllCommand::SelectAllCommand(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~SelectAllCommand
* ���:�Ҹ���
*/
SelectAllCommand::~SelectAllCommand() {
}

/*
* �Լ���Ī:Execute
* ���:�����ϱ� Ŀ��带 �����Ѵ�.
*/
void SelectAllCommand::Execute() {
	Glyph* currentLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;

	//������ �� �ڷ� �̵��Ѵ�. 
	lineOrder = this->notepannel->paper->Last();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->Last();
	//�����ϱ⸦ ���� ��ġ�� �ʱ�ȭ�Ѵ�.
	delete this->notepannel->select;
	this->notepannel->select = new Select(notepannel);
	//�����ϱ⸦ ���� ��ġ�� �̵��Ѵ�.
	this->notepannel->select->MoveCurrent(charIndex, lineOrder);
	//���õǾ��ٴ� ǥ�ø� �ø���.
	this->notepannel->isSelected = TRUE;
	//������Ʈ�� �Ѵ� 
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//Ŭ���̾�Ʈ�� �����Ѵ�.
	this->notepannel->Invalidate(TRUE);
	//ĳ���� ���̰��Ѵ�.
	this->notepannel->caret->ShowCaret();
}