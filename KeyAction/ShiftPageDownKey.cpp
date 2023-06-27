//ShiftPageDownKey.cpp
/*
* 파일명칭:ShiftPageDownKey.cpp
* 기능:shift와 PgDn키를 클릭했을때의 전략
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#include "ShiftPageDownKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "ClientMatrix.h"
#include "ClientLocation.h"
#include "DocumentVirtualSize.h"
#include "Scroll.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"

/*
* 함수명칭:ShiftPageDownKey
* 기능:생성자
*/
ShiftPageDownKey::ShiftPageDownKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~ShiftPageDownKey
* 기능:소멸자
*/
ShiftPageDownKey::~ShiftPageDownKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void ShiftPageDownKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	int lineOrder;
	int charIndex;
	int previousLineWidth;
	int lineNumberInPage = this->notepannel->clientMatrix->lineNumberInPage;
	int clientLineOrder = this->notepannel->clientLocation->lineOrder;
	int availavableLineOrder = this->notepannel->documentVirtualSize->availableLine - 1;

	//현재 줄의 위치를 읽는다.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//현재 줄에서 현재위치의 폭을 구한다.
	previousLineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine, charIndex);
	//아래 페이지로 이동한다.
	if (lineOrder > availavableLineOrder - lineNumberInPage) { //줄의 위치가 마지막 페이지에 위치해 있으면
		//줄의 위치는 클라이언트에서의 위치을 맞춰준 위치이다.
		lineOrder = (lineOrder - clientLineOrder) + availavableLineOrder;
		clientLineOrder = availavableLineOrder;
	}
	else { //줄의 위치가 맨 처음 페이지가 아니면 
		//한 페이지 위로 이동한다.
		lineOrder = lineOrder + lineNumberInPage;
		clientLineOrder = clientLineOrder + lineNumberInPage;
	}
	lineOrder = this->notepannel->paper->Move(lineOrder);
	//이동한 줄에서 이전줄의 폭과 비슷한 위치를 찾아 이동한다. 
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = this->notepannel->characterMatrix->FindNearWidthPosition(currentLine, previousLineWidth);
	charIndex = currentLine->Move(charIndex);
	//클라이언트를 세로로 이동한다.
	this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, clientLineOrder);
	this->notepannel->scroll->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);

	//현재 위치를 구한다. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
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
	PageDownKey pageDownKey(this->notepannel);
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
	pageDownKey.OnKeyDown(0, 0, 0);
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