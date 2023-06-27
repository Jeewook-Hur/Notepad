//ShiftKey.cpp
/*
* 파일명칭:ShiftKey.cpp
* 기능:sfift키를 클릭했을때의 전략
* 작성자:허지욱
* 작성일자:2022/10/18
*/
#include "ShiftKey.h"
#include "Notepannel.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"

/*
* 함수명칭:ShiftKey
* 기능:생성자
*/
ShiftKey::ShiftKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~ShiftKey
* 기능:소멸자
*/
ShiftKey::~ShiftKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void ShiftKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	int lineOrder = -1;
	int charIndex = -2;

	if (this->notepannel->isSelected == FALSE) { //선택되었다는 표시가 내려가 있으면
		lineOrder = this->notepannel->paper->GetCurrent();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		charIndex = currentLine->GetCurrent();

		//선택 클래스를 할당해제 한다.
		delete this->notepannel->select;
		//문서의 현재 위치를 선택하기의 이전 위치로 지정된 선택 클래스를 만든다.
		this->notepannel->select = new Select(notepannel, charIndex, lineOrder, charIndex, lineOrder);
		//선택 중이라는 표시를 띄운다.
		this->notepannel->isSelecting = TRUE;
	}
	else if (this->notepannel->isSelected == TRUE && this->notepannel->isSelecting == FALSE) { //선택되었는데 선택중이라는 표시가 내려가 있으면
		//선택중이라는 표시를 올린다. 
		this->notepannel->isSelecting = TRUE;
	}
}