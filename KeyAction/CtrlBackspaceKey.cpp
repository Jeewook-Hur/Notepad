//CtrlBackspaceKey.cpp
/*
* 파일명칭:CtrlBackspaceKey.cpp
* 기능:컨트롤 백스페이스 키를 눌렀을때의 전략
* 작성자:허지욱
* 작성일자:2022/11/15
*/
#include "CtrlBackspaceKey.h"
#include "Notepannel.h"
#include "Caret.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"
#include "SelectDelete.h"

/*
* 함수명칭:CtrlBackspaceKey
* 기능:생성자
*/
CtrlBackspaceKey::CtrlBackspaceKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~CtrlBackspaceKey
* 기능:소멸자
*/
CtrlBackspaceKey::~CtrlBackspaceKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void CtrlBackspaceKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Glyph* tempLine = NULL;
	Glyph* character = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long tempOrder = -2;
	Long tempLength = -1;
	Long order = 0;
	Long i = 0;
	UINT lineWrapState = -1;


	//종이에서 현재 줄의 위치를 찾는다.
	lineOrder = this->notepannel->paper->GetCurrent();
	//종이에서 현재 줄을 가져온다.
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	//현재 줄에서 현재 단어 위치를 가져온다.
	charIndex = currentLine->GetCurrent();
	//선택하기를 할당해제한다.
	delete this->notepannel->select;
	//현재위치부터 앞의 단어까지 선택한다.
	this->notepannel->select = new Select(notepannel, charIndex, lineOrder, charIndex, lineOrder);
	if (charIndex > -1) {//현재 단어 위치가 맨 처음이 아니면
		//앞의 단어로 이동한다.
		charIndex = currentLine->PreviousWord();
		//앞의 단어까지 선택한다. 
		this->notepannel->select->MoveCurrent(charIndex, lineOrder);
	}
	else if (charIndex <= -1 && lineOrder > 0) {//현재 단어 위치가 맨 처음이고 현재 줄이 맨 처음이 아니면
		//앞의 줄로 이동한다.
		lineOrder = this->notepannel->paper->Previous();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		//앞의 줄의 끝으로 이동한다. 
		charIndex = currentLine->Last();
		//앞의 줄의 끝까지 선택한다. 
		this->notepannel->select->MoveCurrent(charIndex, lineOrder);
	}
	//선택한 영역을 지운다. 
	SelectDelete selectDelete(this->notepannel);
	selectDelete.OnKeyDown(nChar, nRepCnt, nFlags);
}