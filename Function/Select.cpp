//Select.cpp
/*
* ���ϸ�Ī:Select.cpp
* ���:�����ϱ⿡ ���� ����� �����ϴ� Ŭ����
* �ۼ���:������
* �ۼ�����:20221014
*/
#include "Select.h"
#include "Notepannel.h"
#include "Paper.h"

/*
* �Լ���Ī:Select
* ���:������
*/
Select::Select(Notepannel* notepannel, int previousXIndex, int previousLineOrder, int currentXIndex, int currentLineOrder):notepannel(notepannel) {
	//�� ����
	this->previousXIndex = previousXIndex;
	this->previousLineOrder = previousLineOrder;
	this->currentXIndex = currentXIndex;
	this->currentLineOrder = currentLineOrder;
	//ũ�⿡ ���� �з�
	if (this->currentLineOrder > this->previousLineOrder) {
		this->frontXIndex = this->previousXIndex;
		this->frontLineOrder = this->previousLineOrder;
		this->endXIndex = this->currentXIndex;
		this->endLineOrder = this->currentLineOrder;
	}
	else if (this->currentLineOrder == this->previousLineOrder && this->currentXIndex >= this->previousXIndex) {
		this->frontXIndex = this->previousXIndex;
		this->frontLineOrder = this->previousLineOrder;
		this->endXIndex = this->currentXIndex;
		this->endLineOrder = this->currentLineOrder;
	}
	else {
		this->frontXIndex = this->currentXIndex;
		this->frontLineOrder = this->currentLineOrder;
		this->endXIndex = this->previousXIndex;
		this->endLineOrder = this->previousLineOrder;
	}

	if (!(this->frontLineOrder == this->endLineOrder && this->frontXIndex == this->endXIndex)) {
		this->notepannel->isSelected = TRUE;
	}

	if (this->frontLineOrder == this->endLineOrder && this->frontXIndex == this->endXIndex) {
		this->frontXIndex = -1;
		this->frontLineOrder = 0;
		this->endXIndex = -1;
		this->endLineOrder = 0;
		this->notepannel->isSelected = FALSE;
	}

}

/*
* �Լ���Ī:~Select
* ���:�Ҹ���
*/
Select::~Select() {
	this->notepannel->isSelected = FALSE;
}

/*
* �Լ���Ī:MoveCurrent
* ���:�Է¹��� ��ġ�� ���� ��ġ�� �ű��.
*/
void Select::MoveCurrent(int currentXIndex, int currentLineOrder) {
	//����
	this->currentXIndex = currentXIndex;
	this->currentLineOrder = currentLineOrder;
	//ũ�⿡ ���� �з�
	if (this->currentLineOrder > this->previousLineOrder) {
		this->frontXIndex = this->previousXIndex;
		this->frontLineOrder = this->previousLineOrder;
		this->endXIndex = this->currentXIndex;
		this->endLineOrder = this->currentLineOrder;
	}
	else if (this->currentLineOrder == this->previousLineOrder && this->currentXIndex >= this->previousXIndex) {
		this->frontXIndex = this->previousXIndex;
		this->frontLineOrder = this->previousLineOrder;
		this->endXIndex = this->currentXIndex;
		this->endLineOrder = this->currentLineOrder;
	}
	else {
		this->frontXIndex = this->currentXIndex;
		this->frontLineOrder = this->currentLineOrder;
		this->endXIndex = this->previousXIndex;
		this->endLineOrder = this->previousLineOrder;
	}

	if (!(this->frontLineOrder == this->endLineOrder && this->frontXIndex == this->endXIndex)) {
		this->notepannel->isSelected = TRUE;
	}


}

/*
* �Լ���Ī:IsSelected
* ���:������ �Է��ϸ� ���õǾ����� Ȯ���Ѵ�.
*/
BOOL Select::IsSelected(int lineOrder, int charOrder) {
	BOOL ret = FALSE;


	if (lineOrder == this->frontLineOrder && lineOrder != this->endLineOrder && charOrder > this->frontXIndex) { //������ ������ �Ǿ����̸�
		ret = TRUE;
	}
	else if (lineOrder > this->frontLineOrder && lineOrder < this->endLineOrder) { //������ ������ �߰����̸�
		ret = TRUE;
	}
	else if (lineOrder != frontLineOrder && lineOrder == this->endLineOrder && charOrder <= this->endXIndex) { //������ ������ ������ ���̸�
		ret = TRUE;
	}
	else if (lineOrder == this->frontLineOrder && lineOrder == this->endLineOrder && charOrder > this->frontXIndex && charOrder <= this->endXIndex) { //���ÿ����� �����̸�
		ret = TRUE;
	}
	return ret;
}


/*
* �Լ���Ī:IsEqual
* ���:���ù��� ��ġ�� �Է¹��� ���̿� ��ġ�ϴ��� Ȯ���Ѵ�. 
*/
BOOL Select::IsEqual(Glyph* other) {
	BOOL ret = FALSE;
	Glyph* clone = 0;
	
	clone = this->notepannel->paper->Clone(this->frontLineOrder, this->frontXIndex, this->endLineOrder, this->endXIndex);
	if (clone->IsEqual(other)) {
		ret = TRUE;
	}

	delete clone;
	return ret;
}
