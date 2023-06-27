//DeleteCommand.cpp
/*
* 파일명칭:DeleteCommand.cpp
* 기능:Delete키 커멘드
* 작성자:허지욱
* 작성일자:2022/11/21
*/
#include "DeleteCommand.h"
#include "Notepannel.h"
#include "Select.h"

#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"

#include "KeyAction.h"
#include "KeyActionCreator.h"

/*
* 함수명칭:DeleteCommand
* 기능:생성자
*/
DeleteCommand::DeleteCommand(Notepannel* notepannel) : notepannel(notepannel) {
	SHORT ctrlKeyState = GetKeyState(VK_CONTROL);
	SHORT shiftKeyState = GetKeyState(VK_SHIFT);
	BOOL isSelected = this->notepannel->isSelected;
	Glyph* currentLine = NULL;
	Glyph* nextLine = NULL;
	Glyph* endLine = NULL;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long endLineOrder = -1;
	Long endCharIndex = -2;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long paperLength = 0;
	Long lineLength = -1;

	this->wasSelected = FALSE;;


	//현재 위치를 구한다. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	//현대 위치에 시작 위치를 대입한다.
	frontLineOrder = lineOrder;
	frontCharIndex = charIndex;

	//종이의 길이와 현재 줄의 길이를 구한다. 
	paperLength = this->notepannel->paper->GetLength();
	lineLength = currentLine->GetLength();

	if (lineOrder < paperLength - 1) {
		nextLine = this->notepannel->paper->GetAt(lineOrder + 1);
	}

	if (charIndex >= lineLength - 1 && lineOrder < paperLength - 1 && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) {
		//현재 위치가 맨 끝이고 현재 줄이 맨 끝이 아니고 딜리트키만 눌렀을 때
		//다음 줄의 맨 앞을 끝 위치로 지정한다.
		endLineOrder = lineOrder + 1;
		endCharIndex = -1;
	}
	else if (charIndex < lineLength - 1 && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) { 
		//현재 위치가 맨 끝이 아니고 딜리트키만 눌렀을 때
		endLineOrder = frontLineOrder;
		endCharIndex = frontCharIndex + 1;
	}
	else if (charIndex >= lineLength - 1 && lineOrder < paperLength - 1 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) { 
		//현재 위치가 맨 끝이고 현재 줄이 맨 끝이 아니고 ctrl+딜리트키를 눌렀을 때
		endLineOrder = lineOrder + 1;
		endLine = this->notepannel->paper->GetAt(endLineOrder);
		endLine->First();
		endCharIndex = endLine->NextWord();
	}
	else if (charIndex < lineLength - 1 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) { 
		//현재 위치가 맨 끝이 아니고 ctrl+딜리트키를 눌렀을 때
		endLineOrder = frontLineOrder;
		endCharIndex = currentLine->NextWord();
	}
	else if (charIndex >= lineLength - 1 && lineOrder < paperLength - 1 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000) && isSelected == FALSE) {
		//현재 위치가 맨 끝이고 현재 줄이 맨 끝이 아니고 ctrl+shift+delete 키를 눌렀을 때
		endLineOrder = lineOrder + 1;
		endLine = this->notepannel->paper->GetAt(endLineOrder);
		endCharIndex = endLine->Last();
	}
	else if (charIndex < lineLength - 1 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000) && isSelected == FALSE) {
		//현재 위치가 맨 끝이 아니고 ctrl+shift+delete 키를 눌렀을 때
		endLineOrder = frontLineOrder;
		endCharIndex = currentLine->Last();
	}
	else if (isSelected == TRUE) { //선택되었을 때 딜리트키를 눌렀을 때
		this->wasSelected = TRUE;
		frontLineOrder = this->notepannel->select->frontLineOrder;
		frontCharIndex = this->notepannel->select->frontXIndex;
		endLineOrder = this->notepannel->select->endLineOrder;
		endCharIndex = this->notepannel->select->endXIndex;
		
	}

	if (charIndex >= lineLength - 1 && lineOrder < paperLength - 1 && dynamic_cast<DummyLine*>(nextLine) && isSelected == FALSE) {
		endCharIndex++;
	}

	//지울 위치의 절대 위치를 저장한다.
	this->notepannel->paper->GetLocation(frontLineOrder, frontCharIndex, &this->frontLineLocation, &this->frontCharLocation);
	this->notepannel->paper->GetLocation(endLineOrder, endCharIndex, &this->endLineLocation, &this->endCharLocation);

	//지울 위치의 복제본을 구한다. 
	this->previousPaper = this->notepannel->paper->Clone(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);
	this->previousPaper->MergeAllDummyLines();
}

/*
* 함수명칭:~DeleteCommand
* 기능:소멸자
*/
DeleteCommand::~DeleteCommand() {
	delete this->previousPaper;
}

/*
* 함수명칭:Execute
* 기능:커멘드를 실행하다
*/
void DeleteCommand::Execute() {
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

	//선택클래스를 초기화한다.
	delete this->notepannel->select;
	this->notepannel->select = new Select(notepannel);

#if 0
	KeyActionCreator keyActionCreator(this->notepannel);
	KeyAction* keyAction = NULL;

	keyAction = keyActionCreator.Create(VK_DELETE, 0, 0);
	if (keyAction != NULL) {
		keyAction->OnKeyDown(VK_DELETE, 0, 0);
	}
	delete keyAction;
#endif
}

/*
* 함수명칭:UnExecute
* 기능:커멘드를 실행취소한다. 
*/
void DeleteCommand::UnExecute() {
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
	//삽입한 위치의 앞으로 이동한다. 
	lineOrder = this->notepannel->paper->Move(frontLineOrder);
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	currentLine->Move(frontCharIndex);

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