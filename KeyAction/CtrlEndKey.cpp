//CtrlEndKey.cpp
/*
* 파일명칭:CtrlEndKey.cpp
* 기능:컨트롤과 엔드키를 클릭했을때의 전략
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#include "CtrlEndKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Scroll.h"
#include "DocumentVirtualSize.h"
#include "Select.h"

/*
* 함수명칭:CtrlEndKey
* 기능:생성자
*/
CtrlEndKey::CtrlEndKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~CtrlEndKey
* 기능:소멸자
*/
CtrlEndKey::~CtrlEndKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void CtrlEndKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long xToMove = this->notepannel->documentVirtualSize->availableX;
	BOOL xOut = FALSE;
	BOOL yOut = FALSE;

	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);

	lineOrder = this->notepannel->paper->Last();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->Last();

	
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