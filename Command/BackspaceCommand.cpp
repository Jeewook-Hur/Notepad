//BackspaceCommand.cpp
/*
* 파일명칭:BackspaceCommand.cpp
* 기능:백스페이스 커멘드
* 작성자:허지욱
* 작성일자:2022/12/2
*/
#include "BackspaceCommand.h"
#include "Notepannel.h"
#include "Select.h"

#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"

#include "KeyAction.h"
#include "KeyActionCreator.h"

/*
* 함수명칭:BackspaceCommand
* 기능:생성자
*/
BackspaceCommand::BackspaceCommand(Notepannel* notepannel, UINT nChar, UINT nRepCnt, UINT nFlags) : notepannel(notepannel) {
	SHORT ctrlKeyState = GetKeyState(VK_CONTROL);
	SHORT shiftKeyState = GetKeyState(VK_SHIFT);
	BOOL isSelected = this->notepannel->isSelected;
	Glyph* currentLine = NULL;
	Glyph* frontLine = NULL;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long endLineOrder = -1;
	Long endCharIndex = -2;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long lineLength = -1;

	this->wasSelected = FALSE;;

	//현재 위치를 구한다. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	//현대 위치에 마지막 위치를 대입한다.
	endLineOrder = lineOrder;
	endCharIndex = charIndex;

	if (charIndex <= -1 && lineOrder > 0 && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) {
		//현재 위치가 맨 앞이고 현재 줄이 맨 앞이 아니고 백스페이스키만 눌렀을 때
		//이전 줄의 맨 뒤를 끝 위치로 지정한다.
		frontLineOrder = lineOrder - 1;
		frontLine = this->notepannel->paper->GetAt(frontLineOrder);
		frontCharIndex = frontLine->Last();
	}
	else if (charIndex > -1 && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) {
		//현재 위치가 맨 앞이 아니고 백스페이스키만 눌렀을 때
		frontLineOrder = endLineOrder;
		frontCharIndex = endCharIndex - 1;
	}
	else if (charIndex <= -1 && lineOrder > 0 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) {
		//현재 위치가 맨 앞이고 현재 줄이 맨 앞이 아니고 ctrl+백스페이스키를 눌렀을 때
		frontLineOrder = lineOrder - 1;
		frontLine = this->notepannel->paper->GetAt(frontLineOrder);
		frontLine->Last();
		frontCharIndex = frontLine->PreviousWord();
	}
	else if (charIndex > -1 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) {
		//현재 위치가 맨 앞이 아니고 ctrl+백스페이스키를 눌렀을 때
		frontLineOrder = endLineOrder;
		frontCharIndex = currentLine->PreviousWord();
	}
	else if (charIndex <= -1 && lineOrder > 0 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000) && isSelected == FALSE) {
		//현재 위치가 맨 앞이고 현재 줄이 맨 앞이 아니고 ctrl+shift+backspace 키를 눌렀을 때
		frontLineOrder = lineOrder - 1;
		frontLine = this->notepannel->paper->GetAt(endLineOrder);
		frontCharIndex = frontLine->First();
	}
	else if (charIndex > -1 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000) && isSelected == FALSE) {
		//현재 위치가 맨 앞이 아니고 ctrl+shift+backspace 키를 눌렀을 때
		frontLineOrder = endLineOrder;
		frontCharIndex = currentLine->First();
	}
	else if (isSelected == TRUE) { //선택되었을 때 백스페이스키를 눌렀을 때
		this->wasSelected = TRUE;
		frontLineOrder = this->notepannel->select->frontLineOrder;
		frontCharIndex = this->notepannel->select->frontXIndex;
		endLineOrder = this->notepannel->select->endLineOrder;
		endCharIndex = this->notepannel->select->endXIndex;
	}

	if (dynamic_cast<DummyLine*>(currentLine) && charIndex <= -1 && lineOrder > 0 && isSelected == FALSE) {
		frontCharIndex--;
	}

	//지울 위치의 절대 위치를 저장한다.
	this->notepannel->paper->GetLocation(endLineOrder, endCharIndex, &this->endLineLocation, &this->endCharLocation);
	this->notepannel->paper->GetLocation(frontLineOrder, frontCharIndex, &this->frontLineLocation, &this->frontCharLocation);

	//지울 위치의 복제본을 구한다. 
	this->previousPaper = this->notepannel->paper->Clone(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);
	this->previousPaper->MergeAllDummyLines();
}

/*
* 함수명칭:~BackspaceCommand
* 기능:소멸자
*/
BackspaceCommand::~BackspaceCommand() {
	delete this->previousPaper;
}

/*
* 함수명칭:Execute
* 기능:커멘드를 실행하다
*/
void BackspaceCommand::Execute() {
	Glyph* currentLine = 0;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long endLineOrder = -1;
	Long endCharIndex = -2;

	//더미열 병합
	this->notepannel->paper->MergeAllDummyLines();

	//절대 위치를 현재 위치로 치환한다.
	this->notepannel->paper->MoveToLocation(this->frontLineLocation, this->frontCharLocation, &frontLineOrder, &frontCharIndex);
	this->notepannel->paper->MoveToLocation(this->endLineLocation, this->endCharLocation, &endLineOrder, &endCharIndex);

	//선택 범위의 내용을 지운다. 
	this->notepannel->paper->Remove(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);

	//앞쪽 위치로 이동한다.
	this->notepannel->paper->Move(frontLineOrder);
	this->notepannel->paper->GetAt(frontLineOrder)->Move(frontCharIndex);

	//선택클래스를 초기화한다.
	delete this->notepannel->select;
	this->notepannel->select = new Select(notepannel);

}

/*
* 함수명칭:UnExecute
* 기능:커멘드를 실행취소한다.
*/
void BackspaceCommand::UnExecute() {
	Glyph* currentLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long endLineOrder = -1;
	Long endCharIndex = -2;


	//더미열 병합
	this->notepannel->paper->MergeAllDummyLines();


	//앞쪽 절대 위치를 현재 위치로 치환한다.
	this->notepannel->paper->MoveToLocation(this->frontLineLocation, this->frontCharLocation, &frontLineOrder, &frontCharIndex);
	//지운 위치에 기억한 내용을 삽입한다.
	this->notepannel->paper->Add(this->previousPaper, frontLineOrder, frontCharIndex);
	//뒤쪽 절대 위치를 현재 위치로 치환한다.
	this->notepannel->paper->MoveToLocation(this->endLineLocation, this->endCharLocation, &endLineOrder, &endCharIndex);
	//삽입한 위치의 끝으로 이동한다. 
	lineOrder = this->notepannel->paper->Move(endLineOrder);
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	currentLine->Move(endCharIndex);
	
	if (this->wasSelected == TRUE) {
		//복구한 위치를 선택한다. 
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);
	}
	else { //선택하지 않았어도 디폴트로 선택해제해준다.
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel);
	}
}