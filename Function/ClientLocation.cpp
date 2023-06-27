//ClientLocation.cpp
/*
* ���ϸ�Ī:ClientLocation.cpp
* ���:Ŭ���̾�Ʈ�� ������ ���� ��ǥ�� ��Ÿ���� ����
* �ۼ���:������
* �ۼ�����:20220923
*/
#include "ClientLocation.h"
#include "Notepannel.h"
#include "Caret.h"
#include "DocumentVirtualSize.h"
#include "CharacterMatrix.h"
#include "ClientMatrix.h"
//#include "Scroll.h"
#include "Paper.h"
#include "Line.h"
/*
* �Լ���Ī:ClientLocation
* ���:������
*/
ClientLocation::ClientLocation(Notepannel* notepannel) :notepannel(notepannel) {
	this->x = 0;
	this->lineOrder = 0;
//	this->lastPage = 0;
}

/*
* �Լ���Ī:~ClientLocation
* ���:�Ҹ���
*/
ClientLocation::~ClientLocation() {
}

/*
* �Լ���Ī:Move
* ���:�Է¹��� ��ǥ�� ��ġ�� �̵��Ѵ�.
*/
void ClientLocation::Move(int x, int lineOrder) { //�̵��� ��ġ�� �Է¹޴´�. 
	int clientWidth;
	int clientHeight;
	int characterHeight;
	int remainder;


	//Ŭ���̾�Ʈ�� ���� �� ���� ������ ����Ѵ�.
	characterHeight = this->notepannel->characterMatrix->height;
	clientWidth = this->notepannel->clientMatrix->width;
	clientHeight = this->notepannel->clientMatrix->height;

	remainder = clientHeight % characterHeight;

	//�Է¹��� x���� �����Ѵ�.
	this->x = x;
	if (this->x > this->notepannel->documentVirtualSize->availableX) {
		//�Է¹��� x��ǥ�� Ŭ���̾�Ʈ��ǥ ���ɰ��� �ִ밪 �̻��̸� 
		//x��ǥ�� �ִ����� �����Ѵ�. 
		this->x = this->notepannel->documentVirtualSize->availableX;
	}
	else if (this->notepannel->documentVirtualSize->MaxX <= clientWidth) {
		//������ ���ΰ���ũ�Ⱑ Ŭ���̾�Ʈ ũ�⺸�� ������ Ŭ���̾�Ʈ ��ġ�� �� ���̴�. 
		this->x = 0;
	}
	else if (this->x < 0) {
		this->x = 0;
	}

	//�Է¹��� ���� ������ �Է��Ѵ�. 
	//this->lastPage = 0; //������ ������ ������ ������ �����ϴ� �÷���
	this->lineOrder = lineOrder;
	if (this->lineOrder > this->notepannel->documentVirtualSize->availableLine - 1 && clientHeight > characterHeight) {
		//�Է¹��� ���� ������ Ŭ���̾�Ʈ ��ǥ ���ɰ��� �ִ밳�� �̻��̸�
		//y��ġ�� �ִ����� �����Ѵ�. 
		this->lineOrder = this->notepannel->documentVirtualSize->availableLine;
		//if (remainder != 0) { //Ŭ���̾�Ʈ�� ���� ũ�Ⱑ �ټ��� �� �¾� �������� ������
		//	//�÷��׸� ����. 
		//	this->lastPage = 1;
		//}
	}
	else if (this->notepannel->documentVirtualSize->MaxY <= clientHeight) {
		//������ ���ΰ���ũ�Ⱑ Ŭ���̾�Ʈ ũ�⺸�� ������ Ŭ���̾�Ʈ ��ġ�� �� ���̴�. 
		this->lineOrder = 0;
	}
	else if (clientHeight <= characterHeight) {//Ŭ���̾�Ʈ�� ���̰� ������ ���̺��� ������
		//������ ó������ �����Ѵ�. 
		this->lineOrder = 0;
	}
	else if (this->lineOrder < 0) {
		this->lineOrder = 0;
	}
}










#if 0
/*
* �Լ���Ī:MoveToCurrent
* ���:���� ��ġ�� �°� �̵��Ѵ�.
*/
void ClientLocation::MoveToCurrent() {
	Glyph* currentLine;
	int lineOrder;
	int charIndex;
	int currentWidth;

	//���� ��ġ�� �д´�.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	currentWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine, charIndex);

	//���� ��ġ�� �����ϴ� Ŭ���̾�Ʈ ��ġ�� �̵��Ѵ�. 
	this->Move(currentWidth, lineOrder);
	//��ũ���� �����.
	this->notepannel->scroll->MoveToClientLocation();
	//�ٲ� ��ġ�� �°� ĳ���� �������ش�. 
	this->notepannel->Notify();
}

/*
* �Լ���Ī:MoveBackInPercentage
* ���:�Է¹��� ��ŭ Ŭ���̾�Ʈ ��ġ�� �����Ѵ�.
*/
void ClientLocation::MoveBackInPercentage(int percentageX, int percentageY) {
	int xBack;
	int yBack;
	int clientWidth;
	clientWidth = this->notepannel->clientMatrix->width;
	
	//�Է¹��� x�伾Ʈ��ŭ ���ش�. 
	xBack = this->x - (clientWidth * percentageX / 100);
	if (xBack < 0) {
		xBack = 0;
	}
	//�Է¹��� y�ۼ�Ʈ ��ŭ ���ش�.
	yBack = this->lineOrder - (this->notepannel->documentVirtualSize->availableLine * percentageY / 100);
	if (yBack < 0) {
		yBack = 0;
	}
	
	//���� ��ġ�� �����ϴ� Ŭ���̾�Ʈ ��ġ�� �̵��Ѵ�. 
	this->Move(xBack, yBack);
	//��ũ���� �����.
	this->notepannel->scroll->MoveToClientLocation();
	//�ٲ� ��ġ�� �°� ĳ���� �������ش�. 
	this->notepannel->Notify();
}



/*
* �Լ���Ī:GetCaretXPercentageInsideClient
* ���:ĳ���� Ŭ���̾�Ʈ�� ���α��� ��� ��ġ���ִ��� ������� ��ȯ�Ѵ�.
*/
int ClientLocation::GetCaretXPercentageInsideClient() {
	int percentage = 0;
	int clientWidth = this->notepannel->clientMatrix->width;
	int caretPosition = this->notepannel->caret->corX;
	
	percentage = (caretPosition - this->x) * 100 / clientWidth;

	return percentage;
}

/*
* �Լ���Ī:GetCaretYPercentageInsideClient
* ���:ĳ���� Ŭ���̾�Ʈ�� ���α��� ��� ��ġ���ִ��� ������� ��ȯ�Ѵ�.
*/
int ClientLocation::GetCaretYPercentageInsideClient() {
	int percentage = 0;
	int clientHeight = this->notepannel->clientMatrix->height;
	int caretPosition = this->notepannel->caret->corY;
	int charHeight = this->notepannel->characterMatrix->height;

	percentage = (caretPosition - this->lineOrder * charHeight) * 100 / clientHeight;

	return percentage;
}


/*
* �Լ���Ī:CheckCaretXIsInside
* ���:ĳ���� X��ġ�� Ŭ���̾�Ʈ ������ ���� �ִ��� Ȯ���Ѵ�.
*/
void ClientLocation::CheckCaretXIsInside(BOOL* isIn, int* distance) {
	int currentCaretX;
	int clientEndPointX;

	*isIn = FALSE;
	*distance = 0;

	//ĳ���� ���� ��ġ�� �޾ƿ´�. 
	currentCaretX = this->notepannel->caret->corX;
	clientEndPointX = this->x + this->notepannel->clientMatrix->width;

	if (currentCaretX >= this->x && currentCaretX <= clientEndPointX) {
		*isIn = TRUE;
	}
	else if (currentCaretX < this->x) {
		*distance = currentCaretX - this->x;
	}
	else if (currentCaretX > clientEndPointX) {
		*distance = currentCaretX - clientEndPointX;
	}
}

/*
* �Լ���Ī:CheckCaretYIsInside
* ���:ĳ���� Y��ġ�� Ŭ���̾�Ʈ ������ ���� �ִ��� Ȯ���Ѵ�.
*/
void ClientLocation::CheckCaretYIsInside(BOOL* isIn, int* distance) {
	int currentCaretY;
	int clientEndPointY;

	*isIn = FALSE;
	*distance = 0;

	//ĳ���� ���� ��ġ�� �޾ƿ´�. 
	currentCaretY = this->notepannel->caret->y;
	clientEndPointY = this->lineOrder + this->notepannel->clientMatrix->lineNumberInPage;

	if (currentCaretY >= this->lineOrder && currentCaretY <= clientEndPointY) {
		*isIn = TRUE;
	}
	else if (currentCaretY < this->lineOrder) {
		*distance = currentCaretY - this->lineOrder;
	}
	else if (currentCaretY > clientEndPointY) {
		*distance = currentCaretY - clientEndPointY;
	}
}


#endif
