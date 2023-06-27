//AutoScrollPositionControl.cpp
/*
* ���ϸ�Ī:AutoScrollPositionControl.cpp
* ���:ĳ���� ���߾� Ŭ���̾�Ʈ�� �ڵ��̵���Ű�� Ŭ����
* �ۼ���:������
* �ۼ�����:2022/10/1
*/
#include "AutoScrollPositionControl.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Scroll.h"
#include "Paper.h"
#include "Line.h"

/*
* �Լ���Ī:AutoScrollPositionControl
* ���:������
*/
AutoScrollPositionControl::AutoScrollPositionControl(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~AutoScrollPositionControl
* ���:�Ҹ���
*/
AutoScrollPositionControl::~AutoScrollPositionControl() {
}

/*
* �Լ���Ī:Update
* ���:�Է¹��� Ŭ������ �´� ������Ʈ�� �Ѵ�.
*/
void AutoScrollPositionControl::Update(Subject* theChangedSubject) {
	this->notepannel->isUpdating = TRUE;


	Glyph* currentLine;
	int lineOrder;
	int charIndex;
	int iineWidth;
	int clientX;
	int clientLineOrder;
	int xToMove;
	int yToMove;
	int lineNumberInPage;

	if (dynamic_cast<Notepannel*>(theChangedSubject)) {//�Է¹��� Ŭ������ �޸����̸�
		if (this->notepannel->clientMoveCheck == TRUE) { //Ŭ���̾�Ʈ�� �ڵ��̵��� �ʿ��� ��Ȳ�̸�
			lineOrder = this->notepannel->paper->GetCurrent();
			currentLine = this->notepannel->paper->GetAt(lineOrder);
			charIndex = currentLine->GetCurrent();
			iineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine, charIndex);
			clientX = this->notepannel->clientLocation->x;
			clientLineOrder = this->notepannel->clientLocation->lineOrder;
			xToMove = this->notepannel->clientLocation->x;
			yToMove = this->notepannel->clientLocation->lineOrder;
			lineNumberInPage = this->notepannel->clientMatrix->lineNumberInPage;

			//���� ��ġ�� Ŭ���̾�Ʈ���� ���η� ������� Ȯ���Ѵ�.  
			if (iineWidth < clientX) { //���� ��ġ�� Ŭ���̾�Ʈ�� �����̸� 
				//Ŭ���̾�Ʈ�� ����� �� �� ������ ĳ���� ���� �̵��Ѵ�.
				xToMove = iineWidth - this->notepannel->clientMatrix->widthOneThird;
				this->notepannel->clientLocation->Move(xToMove, yToMove);
				//��ũ���� Ŭ���̾�Ʈ ��ġ�� �����.
				this->notepannel->scroll->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);
				this->notepannel->Invalidate(TRUE);
			}
			else if (iineWidth > clientX + this->notepannel->clientMatrix->width) {//���� ��ġ�� Ŭ���̾�Ʈ�� �������̸� 
				//Ŭ���̾�Ʈ�� ����� �� �� ������ ĳ���� ���� �̵��Ѵ�.
				xToMove = iineWidth - (this->notepannel->clientMatrix->widthOneThird * 2);
				this->notepannel->clientLocation->Move(xToMove, yToMove);
				//��ũ���� Ŭ���̾�Ʈ ��ġ�� �����.
				this->notepannel->scroll->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);
				this->notepannel->Invalidate(TRUE);
			}
			//���� ��ġ�� Ŭ���̾�Ʈ���� ���η� ������� Ȯ���Ѵ�.
			if (lineOrder < clientLineOrder) {//���� ��ġ�� Ŭ���̾�Ʈ�� ���� 
				//Ŭ���̾�Ʈ�� ĳ���� �ִ� ��ġ���� �ø���
				yToMove = lineOrder;
				this->notepannel->clientLocation->Move(xToMove, yToMove);
				//��ũ���� Ŭ���̾�Ʈ ��ġ�� �����.
				this->notepannel->scroll->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);
				this->notepannel->Invalidate(TRUE);
			}
			else if (lineOrder > clientLineOrder + lineNumberInPage - 1) {//���� ��ġ�� Ŭ���̾�Ʈ�� �Ʒ��� 
				//Ŭ���̾�Ʈ�� ĳ���� ���� ��ġ���� ������.
				yToMove = lineOrder - lineNumberInPage + 1;
				this->notepannel->clientLocation->Move(xToMove, yToMove);
				//��ũ���� Ŭ���̾�Ʈ ��ġ�� �����.
				this->notepannel->scroll->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);
				this->notepannel->Invalidate(TRUE);
			}


			//�ڵ��̵� üũ�� ����. 
			this->notepannel->clientMoveCheck = FALSE;
		}
	}
	this->notepannel->isUpdating = FALSE;
}
