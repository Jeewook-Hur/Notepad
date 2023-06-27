//DownKey.cpp
/*
* 파일명칭:DownKey.cpp
* 기능:아래 화살표를 클릭했을때의 전략
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#include "DownKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"

/*
* 함수명칭:DownKey
* 기능:생성자
*/
DownKey::DownKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~DownKey
* 기능:소멸자
*/
DownKey::~DownKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void DownKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	int lineOrder = -1;
	int previousLineWidth = 0;
	int charIndex = -2;
	int clientLineOrder = this->notepannel->clientLocation->lineOrder;
	int lineNumberInPage = this->notepannel->clientMatrix->lineNumberInPage;
	int lineInClientEnd = clientLineOrder + lineNumberInPage;

	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	//현재 줄의 현재 위치의 폭을 구한다.
	previousLineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine, charIndex);

	//현재 위치에 맞게 이동한다.
	if (lineOrder >= clientLineOrder && lineOrder <= lineInClientEnd) { //현재 위치가 클라이언트 안에 있으면
		//다음줄로 이동한다.
		lineOrder = this->notepannel->paper->Next();
	}
	else if (lineOrder < clientLineOrder) { //현재 위치가 클라이언트 위에 있으면
		//클라이언트 위치 바로 위로 이동한다
		lineOrder = this->notepannel->paper->Move(clientLineOrder - 1);
	}
	else if (lineOrder > lineInClientEnd) { //현재 위치가 클라이언트 아래에 있으면
		//클라이언트 위치 바로 아래로 이동한다.
		lineOrder = this->notepannel->paper->Move(lineInClientEnd + 1);
	}

	//지정된에서 이전줄과 근접한 위치로 이동한다.
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = this->notepannel->characterMatrix->FindNearWidthPosition(currentLine, previousLineWidth);
	currentLine->Move(charIndex);
	//현재 위치로 선택 클래스를 초기화한다. 
	delete this->notepannel->select;
	this->notepannel->select = new Select(this->notepannel, charIndex, lineOrder, charIndex, lineOrder);
	//업데이트 갱신 함수를 호출한다.
	//캐럿을 업데이트 한다. 
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//클라이언트 갱신 함수를 호출한다.
	this->notepannel->Invalidate(TRUE);
	//캐럿을 보이게한다.
	this->notepannel->caret->ShowCaret();
}