//CutCommand.cpp
/*
* 파일명칭:CutCommand.cpp
* 기능:잘라내기를 하는 커멘드
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#include "CutCommand.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "KeyAction.h"
#include "KeyActionCreator.h"
#include "CommandCreator.h"
#include "resource.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"
#include "Document.h"
#include "Caret.h"

/*
* 함수명칭:CutCommand
* 기능:생성자
*/
CutCommand::CutCommand(Notepannel* notepannel) :notepannel(notepannel) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL; Glyph* currentLine = NULL;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long endLineOrder = -1;
	Long endCharIndex = -2;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long lineLength = -1;

	//클립보드에 내용을 저장한다. 
	command = commandCreator.Create(IDM_FORMAT_COPY);
	if (command != NULL) { //커멘트가 반환되었을경우
		command->Execute();
	}
	delete command;

	//현재 위치를 구한다. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	frontLineOrder = this->notepannel->select->frontLineOrder;
	frontCharIndex = this->notepannel->select->frontXIndex;
	endLineOrder = this->notepannel->select->endLineOrder;
	endCharIndex = this->notepannel->select->endXIndex;

	//지울 위치의 절대 위치를 저장한다.
	this->notepannel->paper->GetLocation(endLineOrder, endCharIndex, &this->endLineLocation, &this->endCharLocation);
	this->notepannel->paper->GetLocation(frontLineOrder, frontCharIndex, &this->frontLineLocation, &this->frontCharLocation);

	//지울 위치의 복제본을 구한다. 
	this->previousPaper = this->notepannel->paper->Clone(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);
	this->previousPaper->MergeAllDummyLines();
}

/*
* 함수명칭:~CutCommand
* 기능:소멸자
*/
CutCommand::~CutCommand() {
	delete this->previousPaper;
}

/*
* 함수명칭:Execute
* 기능:자르기 커멘드를 실행한다.
*/
void CutCommand::Execute() {
	KeyActionCreator keyActionCreator(this->notepannel);
	KeyAction* keyAction = NULL;
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

	//문서가 변경되었음을 표시한다. 
	this->notepannel->hasChanged = TRUE;

	//윈도우의 제목을 갱신한다.
	CString windowTitle;
	windowTitle.Format("*%s - Windows 메모장", this->notepannel->document->GetName().c_str());
	this->notepannel->notepad->SetWindowText(windowTitle);

	this->notepannel->documentUploaded = TRUE;
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//delete키의 경우 호출을 안하기에 호출함수가 필요하다. 
	this->notepannel->Invalidate(TRUE);
	//캐럿을 보이게한다.
	this->notepannel->caret->ShowCaret();
}

/*
* 함수명칭:UnExecute
* 기능:자르기 커멘드를 실행취소한다.
*/
void CutCommand::UnExecute() {
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

	//선택했던 위치를 표시한다. 
	delete this->notepannel->select;
	this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);

	//문서가 변경되었음을 표시한다. 
	this->notepannel->hasChanged = TRUE;

	//윈도우의 제목을 갱신한다.
	CString windowTitle;
	windowTitle.Format("*%s - Windows 메모장", this->notepannel->document->GetName().c_str());
	this->notepannel->notepad->SetWindowText(windowTitle);

	this->notepannel->documentUploaded = TRUE;
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//delete키의 경우 호출을 안하기에 호출함수가 필요하다. 
	this->notepannel->Invalidate(TRUE);
	//캐럿을 보이게한다.
	this->notepannel->caret->ShowCaret();
}