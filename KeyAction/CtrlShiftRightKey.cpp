//CtrlShiftRightKey.cpp
/*
* 파일명칭:CtrlShiftRightKey.cpp
* 기능:shift와 오른쪽 화살표를 클릭했을때의 전략
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#include "CtrlShiftRightKey.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Select.h"
#include "DummyLine.h"

/*
* 함수명칭:CtrlShiftRightKey
* 기능:생성자
*/
CtrlShiftRightKey::CtrlShiftRightKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~CtrlShiftRightKey
* 기능:소멸자
*/
CtrlShiftRightKey::~CtrlShiftRightKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void CtrlShiftRightKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Long charIndex = -2;
	Long lineOrder = -1;
	Long order = -2;

	Glyph* nextLine = 0;
	Long nextLineLastIndex = -1;

	Long charIndexMoved = -2;
	Glyph* clonePaper = 0;
	Glyph* lineMerged = 0;
	Long currentLineLastIndex = -1;

	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	if (lineOrder < this->notepannel->paper->GetLength() - 1) {
		nextLine = this->notepannel->paper->GetAt(lineOrder + 1);
		nextLineLastIndex = nextLine->Last();
	}

	if (charIndex < currentLine->GetLength() - 1) {
		charIndexMoved = currentLine->NextWord();

		if (charIndexMoved >= currentLine->GetLength() - 1 && lineOrder < this->notepannel->paper->GetLength() - 1 && dynamic_cast<DummyLine*>(nextLine)) {
			currentLineLastIndex = currentLine->GetLength() - 1;
			clonePaper = this->notepannel->paper->Clone(lineOrder, -1, lineOrder + 1, nextLineLastIndex);
			clonePaper->MergeAllDummyLines();
			lineMerged = clonePaper->GetAt(0);
			lineMerged->Move(currentLineLastIndex);
			lineMerged->PreviousWord();
			charIndexMoved = lineMerged->NextWord();
			if (charIndexMoved > currentLineLastIndex) {
				lineOrder = this->notepannel->paper->Next();
				currentLine = this->notepannel->paper->GetAt(lineOrder);
				currentLine->First();
				currentLine->NextWord();
			}
			delete clonePaper;
		}
	}
	else if (charIndex >= currentLine->GetLength() - 1 && lineOrder < this->notepannel->paper->GetLength() - 1 && !dynamic_cast<DummyLine*>(nextLine)) {
		lineOrder = this->notepannel->paper->Next();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		currentLine->Move(-1);
	}
	else if (charIndex >= currentLine->GetLength() - 1 && lineOrder < this->notepannel->paper->GetLength() - 1 && dynamic_cast<DummyLine*>(nextLine)) {
		lineOrder = this->notepannel->paper->Next();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		currentLine->Move(-1);
		currentLine->NextWord();
	}
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
	CtrlRightKey ctrlRightKey(this->notepannel);
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
	ctrlRightKey.OnKeyDown(0, 0, 0);
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
		this->notepannel->Invalidate(TRUE);
	}
	//캐럿을 보이게한다.
	this->notepannel->caret->ShowCaret();
#endif
}