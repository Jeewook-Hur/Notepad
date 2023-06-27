//CtrlBackspaceKey.cpp
/*
* ���ϸ�Ī:CtrlBackspaceKey.cpp
* ���:��Ʈ�� �齺���̽� Ű�� ���������� ����
* �ۼ���:������
* �ۼ�����:2022/11/15
*/
#include "CtrlBackspaceKey.h"
#include "Notepannel.h"
#include "Caret.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"
#include "SelectDelete.h"

/*
* �Լ���Ī:CtrlBackspaceKey
* ���:������
*/
CtrlBackspaceKey::CtrlBackspaceKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlBackspaceKey
* ���:�Ҹ���
*/
CtrlBackspaceKey::~CtrlBackspaceKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlBackspaceKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Glyph* tempLine = NULL;
	Glyph* character = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long tempOrder = -2;
	Long tempLength = -1;
	Long order = 0;
	Long i = 0;
	UINT lineWrapState = -1;


	//���̿��� ���� ���� ��ġ�� ã�´�.
	lineOrder = this->notepannel->paper->GetCurrent();
	//���̿��� ���� ���� �����´�.
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	//���� �ٿ��� ���� �ܾ� ��ġ�� �����´�.
	charIndex = currentLine->GetCurrent();
	//�����ϱ⸦ �Ҵ������Ѵ�.
	delete this->notepannel->select;
	//������ġ���� ���� �ܾ���� �����Ѵ�.
	this->notepannel->select = new Select(notepannel, charIndex, lineOrder, charIndex, lineOrder);
	if (charIndex > -1) {//���� �ܾ� ��ġ�� �� ó���� �ƴϸ�
		//���� �ܾ�� �̵��Ѵ�.
		charIndex = currentLine->PreviousWord();
		//���� �ܾ���� �����Ѵ�. 
		this->notepannel->select->MoveCurrent(charIndex, lineOrder);
	}
	else if (charIndex <= -1 && lineOrder > 0) {//���� �ܾ� ��ġ�� �� ó���̰� ���� ���� �� ó���� �ƴϸ�
		//���� �ٷ� �̵��Ѵ�.
		lineOrder = this->notepannel->paper->Previous();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		//���� ���� ������ �̵��Ѵ�. 
		charIndex = currentLine->Last();
		//���� ���� ������ �����Ѵ�. 
		this->notepannel->select->MoveCurrent(charIndex, lineOrder);
	}
	//������ ������ �����. 
	SelectDelete selectDelete(this->notepannel);
	selectDelete.OnKeyDown(nChar, nRepCnt, nFlags);
}