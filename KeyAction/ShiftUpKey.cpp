//ShiftUpKey.cpp
/*
* 파일명칭:ShiftUpKey.cpp
* 기능:shift와 위쪽 화살표를 클릭했을때의 전략
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#include "ShiftUpKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"

/*
* 함수명칭:ShiftUpKey
* 기능:생성자
*/
ShiftUpKey::ShiftUpKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~ShiftUpKey
* 기능:소멸자
*/
ShiftUpKey::~ShiftUpKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void ShiftUpKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
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
		//이전줄로 이동한다.
		lineOrder = this->notepannel->paper->Previous();
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

	//현재 위치로 선택 범위를 이동한다.
	this->notepannel->select->MoveCurrent(charIndex, lineOrder);
	//업데이트 갱신 함수를 호출한다.
	//캐럿을 업데이트 한다. 
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//클라이언트 갱신 함수를 호출한다.
	this->notepannel->Invalidate(TRUE);
	//캐럿을 보이게한다.
	this->notepannel->caret->ShowCaret();

#if 0
	UpKey upKey(this->notepannel);
	Glyph* currentLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long previousLineOrder = -1;
	Long previousCharIndex = -2;

	//이동하기 전 위치를 기억한다.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	previousLineOrder = lineOrder;
	previousCharIndex = charIndex;

	//선택되었다는 플래그를 내린다.
	this->notepannel->isSelected = FALSE;
	//선택하기 기능이 적용 안된 방향키의 기능을 수행한다.
	upKey.OnKeyDown(0, 0, 0);
	//선택되었다는 플래그를 올린다.
	this->notepannel->isSelected = TRUE;
	//이동 후 위치를 확인한다.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//이동한 위치가 이전 위치와 다르면
	if (this->notepannel->paper->IsNotEqual(previousLineOrder, previousCharIndex)) {
		//이동한 위치를 선택하기에 갱신한다.
		this->notepannel->select->MoveCurrent(charIndex, lineOrder);
		//클라이언트 갱신 함수를 호출한다.
		this->notepannel->Invalidate(FALSE);
	}
	//캐럿을 보이게한다.
	this->notepannel->caret->ShowCaret();
#endif
}