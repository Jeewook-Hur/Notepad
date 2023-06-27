//ClientLocation.cpp
/*
* 파일명칭:ClientLocation.cpp
* 기능:클라이언트의 문서상 가장 좌표를 나타내는 파일
* 작성자:허지욱
* 작성일자:20220923
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
* 함수명칭:ClientLocation
* 기능:생성자
*/
ClientLocation::ClientLocation(Notepannel* notepannel) :notepannel(notepannel) {
	this->x = 0;
	this->lineOrder = 0;
//	this->lastPage = 0;
}

/*
* 함수명칭:~ClientLocation
* 기능:소멸자
*/
ClientLocation::~ClientLocation() {
}

/*
* 함수명칭:Move
* 기능:입력받은 좌표나 위치로 이동한다.
*/
void ClientLocation::Move(int x, int lineOrder) { //이동할 위치를 입력받는다. 
	int clientWidth;
	int clientHeight;
	int characterHeight;
	int remainder;


	//클라이언트의 길이 및 각종 변수를 계산한다.
	characterHeight = this->notepannel->characterMatrix->height;
	clientWidth = this->notepannel->clientMatrix->width;
	clientHeight = this->notepannel->clientMatrix->height;

	remainder = clientHeight % characterHeight;

	//입력받은 x값을 대입한다.
	this->x = x;
	if (this->x > this->notepannel->documentVirtualSize->availableX) {
		//입력받은 x좌표가 클라이언트좌표 가능값의 최대값 이상이면 
		//x좌표는 최댓값으로 고정한다. 
		this->x = this->notepannel->documentVirtualSize->availableX;
	}
	else if (this->notepannel->documentVirtualSize->MaxX <= clientWidth) {
		//문서의 가로가상크기가 클라이언트 크기보다 작으면 클라이언트 위치는 맨 앞이다. 
		this->x = 0;
	}
	else if (this->x < 0) {
		this->x = 0;
	}

	//입력받은 줄의 순서를 입력한다. 
	//this->lastPage = 0; //문서의 끝에서 여백이 남는지 구분하는 플래그
	this->lineOrder = lineOrder;
	if (this->lineOrder > this->notepannel->documentVirtualSize->availableLine - 1 && clientHeight > characterHeight) {
		//입력받은 줄의 순서가 클라이언트 좌표 가능값의 최대개수 이상이면
		//y위치를 최댓값으로 고정한다. 
		this->lineOrder = this->notepannel->documentVirtualSize->availableLine;
		//if (remainder != 0) { //클라이언트의 세로 크기가 줄수와 딱 맞아 떨어지지 않으면
		//	//플래그를 띄운다. 
		//	this->lastPage = 1;
		//}
	}
	else if (this->notepannel->documentVirtualSize->MaxY <= clientHeight) {
		//문서의 세로가상크기가 클라이언트 크기보다 작으면 클라이언트 위치는 맨 앞이다. 
		this->lineOrder = 0;
	}
	else if (clientHeight <= characterHeight) {//클라이언트의 높이가 한줄의 높이보다 작으면
		//문서의 처음으로 고정한다. 
		this->lineOrder = 0;
	}
	else if (this->lineOrder < 0) {
		this->lineOrder = 0;
	}
}










#if 0
/*
* 함수명칭:MoveToCurrent
* 기능:현재 위치에 맞게 이동한다.
*/
void ClientLocation::MoveToCurrent() {
	Glyph* currentLine;
	int lineOrder;
	int charIndex;
	int currentWidth;

	//현재 위치를 읽는다.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	currentWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine, charIndex);

	//현재 위치에 상정하는 클라이언트 위치로 이동한다. 
	this->Move(currentWidth, lineOrder);
	//스크롤을 맞춘다.
	this->notepannel->scroll->MoveToClientLocation();
	//바뀐 위치에 맞게 캐럿을 조정해준다. 
	this->notepannel->Notify();
}

/*
* 함수명칭:MoveBackInPercentage
* 기능:입력받은 만큼 클라이언트 위치를 후퇴한다.
*/
void ClientLocation::MoveBackInPercentage(int percentageX, int percentageY) {
	int xBack;
	int yBack;
	int clientWidth;
	clientWidth = this->notepannel->clientMatrix->width;
	
	//입력받은 x페센트만큼 빼준다. 
	xBack = this->x - (clientWidth * percentageX / 100);
	if (xBack < 0) {
		xBack = 0;
	}
	//입력받은 y퍼센트 만큼 빼준다.
	yBack = this->lineOrder - (this->notepannel->documentVirtualSize->availableLine * percentageY / 100);
	if (yBack < 0) {
		yBack = 0;
	}
	
	//현재 위치에 상정하는 클라이언트 위치로 이동한다. 
	this->Move(xBack, yBack);
	//스크롤을 맞춘다.
	this->notepannel->scroll->MoveToClientLocation();
	//바뀐 위치에 맞게 캐럿을 조정해준다. 
	this->notepannel->Notify();
}



/*
* 함수명칭:GetCaretXPercentageInsideClient
* 기능:캐럿이 클라이언트의 가로기준 어느 위치에있는지 백분위로 반환한다.
*/
int ClientLocation::GetCaretXPercentageInsideClient() {
	int percentage = 0;
	int clientWidth = this->notepannel->clientMatrix->width;
	int caretPosition = this->notepannel->caret->corX;
	
	percentage = (caretPosition - this->x) * 100 / clientWidth;

	return percentage;
}

/*
* 함수명칭:GetCaretYPercentageInsideClient
* 기능:캐럿이 클라이언트의 세로기준 어느 위치에있는지 백분위로 반환한다.
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
* 함수명칭:CheckCaretXIsInside
* 기능:캐럿의 X위치가 클라이언트 영역에 속해 있는지 확인한다.
*/
void ClientLocation::CheckCaretXIsInside(BOOL* isIn, int* distance) {
	int currentCaretX;
	int clientEndPointX;

	*isIn = FALSE;
	*distance = 0;

	//캐럿의 현재 위치를 받아온다. 
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
* 함수명칭:CheckCaretYIsInside
* 기능:캐럿의 Y위치가 클라이언트 영역에 속해 있는지 확인한다.
*/
void ClientLocation::CheckCaretYIsInside(BOOL* isIn, int* distance) {
	int currentCaretY;
	int clientEndPointY;

	*isIn = FALSE;
	*distance = 0;

	//캐럿의 현재 위치를 받아온다. 
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
