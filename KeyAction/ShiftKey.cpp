//ShiftKey.cpp
/*
* ���ϸ�Ī:ShiftKey.cpp
* ���:sfiftŰ�� Ŭ���������� ����
* �ۼ���:������
* �ۼ�����:2022/10/18
*/
#include "ShiftKey.h"
#include "Notepannel.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"

/*
* �Լ���Ī:ShiftKey
* ���:������
*/
ShiftKey::ShiftKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~ShiftKey
* ���:�Ҹ���
*/
ShiftKey::~ShiftKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void ShiftKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	int lineOrder = -1;
	int charIndex = -2;

	if (this->notepannel->isSelected == FALSE) { //���õǾ��ٴ� ǥ�ð� ������ ������
		lineOrder = this->notepannel->paper->GetCurrent();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		charIndex = currentLine->GetCurrent();

		//���� Ŭ������ �Ҵ����� �Ѵ�.
		delete this->notepannel->select;
		//������ ���� ��ġ�� �����ϱ��� ���� ��ġ�� ������ ���� Ŭ������ �����.
		this->notepannel->select = new Select(notepannel, charIndex, lineOrder, charIndex, lineOrder);
		//���� ���̶�� ǥ�ø� ����.
		this->notepannel->isSelecting = TRUE;
	}
	else if (this->notepannel->isSelected == TRUE && this->notepannel->isSelecting == FALSE) { //���õǾ��µ� �������̶�� ǥ�ð� ������ ������
		//�������̶�� ǥ�ø� �ø���. 
		this->notepannel->isSelecting = TRUE;
	}
}