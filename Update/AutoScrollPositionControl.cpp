//AutoScrollPositionControl.cpp
/*
* 파일명칭:AutoScrollPositionControl.cpp
* 기능:캐럿에 맞추어 클라이언트를 자동이동시키는 클래스
* 작성자:허지욱
* 작성일자:2022/10/1
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
* 함수명칭:AutoScrollPositionControl
* 기능:생성자
*/
AutoScrollPositionControl::AutoScrollPositionControl(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~AutoScrollPositionControl
* 기능:소멸자
*/
AutoScrollPositionControl::~AutoScrollPositionControl() {
}

/*
* 함수명칭:Update
* 기능:입력받은 클래스에 맞는 업데이트를 한다.
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

	if (dynamic_cast<Notepannel*>(theChangedSubject)) {//입력받은 클래스가 메모장이면
		if (this->notepannel->clientMoveCheck == TRUE) { //클라이언트의 자동이동이 필요한 상황이면
			lineOrder = this->notepannel->paper->GetCurrent();
			currentLine = this->notepannel->paper->GetAt(lineOrder);
			charIndex = currentLine->GetCurrent();
			iineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine, charIndex);
			clientX = this->notepannel->clientLocation->x;
			clientLineOrder = this->notepannel->clientLocation->lineOrder;
			xToMove = this->notepannel->clientLocation->x;
			yToMove = this->notepannel->clientLocation->lineOrder;
			lineNumberInPage = this->notepannel->clientMatrix->lineNumberInPage;

			//현재 위치가 클라이언트에서 가로로 벗어났는지 확인한다.  
			if (iineWidth < clientX) { //현재 위치가 클라이언트의 왼쪽이면 
				//클라이언트의 삼분의 일 앞 지점에 캐럿이 오게 이동한다.
				xToMove = iineWidth - this->notepannel->clientMatrix->widthOneThird;
				this->notepannel->clientLocation->Move(xToMove, yToMove);
				//스크롤을 클라이언트 위치에 맞춘다.
				this->notepannel->scroll->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);
				this->notepannel->Invalidate(TRUE);
			}
			else if (iineWidth > clientX + this->notepannel->clientMatrix->width) {//현재 위치가 클라이언트의 오른쪽이면 
				//클라이언트의 삼분의 일 뒤 지점에 캐럿이 오게 이동한다.
				xToMove = iineWidth - (this->notepannel->clientMatrix->widthOneThird * 2);
				this->notepannel->clientLocation->Move(xToMove, yToMove);
				//스크롤을 클라이언트 위치에 맞춘다.
				this->notepannel->scroll->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);
				this->notepannel->Invalidate(TRUE);
			}
			//현재 위치가 클라이언트에서 세로로 벗어났는지 확인한다.
			if (lineOrder < clientLineOrder) {//현재 위치가 클라이언트의 위면 
				//클라이언트를 캐럿이 있는 위치까지 올린다
				yToMove = lineOrder;
				this->notepannel->clientLocation->Move(xToMove, yToMove);
				//스크롤을 클라이언트 위치에 맞춘다.
				this->notepannel->scroll->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);
				this->notepannel->Invalidate(TRUE);
			}
			else if (lineOrder > clientLineOrder + lineNumberInPage - 1) {//현재 위치가 클라이언트의 아래면 
				//클라이언트를 캐럿이 있은 위치까지 내린다.
				yToMove = lineOrder - lineNumberInPage + 1;
				this->notepannel->clientLocation->Move(xToMove, yToMove);
				//스크롤을 클라이언트 위치에 맞춘다.
				this->notepannel->scroll->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);
				this->notepannel->Invalidate(TRUE);
			}


			//자동이동 체크를 끈다. 
			this->notepannel->clientMoveCheck = FALSE;
		}
	}
	this->notepannel->isUpdating = FALSE;
}
