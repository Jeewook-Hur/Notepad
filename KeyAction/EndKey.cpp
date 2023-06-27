//EndKey.cpp
/*
* 파일명칭:EndKey.cpp
* 기능:엔드키를 클릭했을때의 전략
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#include "EndKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"

/*
* 함수명칭:EndKey
* 기능:생성자
*/
EndKey::EndKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~EndKey
* 기능:소멸자
*/
EndKey::~EndKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void EndKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;

	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);

	currentLine->Last();

	//현재 위치를 구한다. 
	charIndex = currentLine->GetCurrent();
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