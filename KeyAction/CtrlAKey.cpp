//CtrlAKey.cpp
/*
* ���ϸ�Ī:CtrlAKey.cpp
* ���:ctrl�� AŰ�� ���������� ����
* �ۼ���:������
* �ۼ�����:2022/11/15
*/
#include "CtrlAKey.h"
#include "Notepannel.h"
#include "Command.h"
#include "CommandCreator.h"
#include "resource.h"

#if 0
#include "Caret.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"
#endif

/*
* �Լ���Ī:CtrlAKey
* ���:������
*/
CtrlAKey::CtrlAKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlAKey
* ���:�Ҹ���
*/
CtrlAKey::~CtrlAKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlAKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	//�Է¹��� �޴��� �´� Ŀ��带 �����.
	command = commandCreator.Create(IDM_FORMAT_SELECTALL);
	if (command != NULL) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
		command->Execute();
	}
	delete command;
#if 0
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
#endif
}