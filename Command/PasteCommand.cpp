//PasteCommand.cpp
/*
* 파일명칭:PasteCommand.cpp
* 기능:붙여넣기를 하는 커멘드
* 작성자:허지욱
* 작성일자:2022/11/21
*/
#include "PasteCommand.h"
#include "Notepannel.h"
#include "Clipboard.h"
#include "KeyAction.h"
#include "KeyActionCreator.h"
#include "Command.h"
#include "CommandCreator.h"
#include "Caret.h"
#include "Select.h"
#include "MacroCommand.h"
#include "GlyphCreater.h"
#include "Paper.h"
#include "Line.h"
#include "resource.h"
#include <string>
using namespace std;

/*
* 함수명칭:PasteCommand
* 기능:생성자
*/
PasteCommand::PasteCommand(Notepannel* notepannel) :notepannel(notepannel) {
	GlyphCreater glyphCreater;
	Glyph* currentLine = NULL;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long lineLength = -1;
	string stringToAdd;

	//선택되었으면 선택된 영역을 지운다. 
	CommandCreator commandCreator(this->notepannel);
	Command* command = 0;
	if (this->notepannel->isSelected == TRUE) {
		command = commandCreator.Create(IDM_FORMAT_DELETE);
		command->Execute();
		this->notepannel->macroCommand->Add(command);
	}

	//현재 위치를 구한다. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	frontLineOrder = lineOrder;
	frontCharIndex = charIndex;

	//지울 위치의 절대 위치를 저장한다.
	this->notepannel->paper->GetLocation(frontLineOrder, frontCharIndex, &this->frontLineLocation, &this->frontCharLocation);

	this->endLineLocation = -1;
	this->endCharLocation = -2;

	//클립보드 클래스에서 문자열을 가져온다.
	stringToAdd = this->notepannel->clipboard->GetData();
	//문자열을 종이형으로 치환한다. 
	this->previousPaper = glyphCreater.Create(stringToAdd);
}
PasteCommand::PasteCommand(Notepannel* notepannel, Glyph* paper) :notepannel(notepannel){
	Glyph* currentLine = NULL;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long lineLength = -1;

	//선택되었으면 선택된 영역을 지운다. 
	CommandCreator commandCreator(this->notepannel);
	Command* command = 0;
	if (this->notepannel->isSelected == TRUE) {
		command = commandCreator.Create(IDM_FORMAT_DELETE);
		command->Execute();
		this->notepannel->macroCommand->Add(command);
	}

	//현재 위치를 구한다. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	frontLineOrder = lineOrder;
	frontCharIndex = charIndex;

	//지울 위치의 절대 위치를 저장한다.
	this->notepannel->paper->GetLocation(frontLineOrder, frontCharIndex, &this->frontLineLocation, &this->frontCharLocation);

	this->endLineLocation = -1;
	this->endCharLocation = -2;

	this->previousPaper = paper->Clone();
	this->previousPaper->MergeAllDummyLines();

}

/*
* 함수명칭:~PasteCommand
* 기능:소멸자
*/
PasteCommand::~PasteCommand() {
	delete this->previousPaper;
}

/*
* 함수명칭:Execute
* 기능:복사하기 커멘드를 실행한다.
*/
void PasteCommand::Execute() {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	KeyActionCreator keyActionCreator(this->notepannel);
	KeyAction* keyAction = NULL;
	Glyph* currentLine = NULL;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long endLineOrder = -1;
	Long endCharIndex = -2;
	Long lineOrder = -1;
	Long charIndex = -2;

	//더미열 병합
	this->notepannel->paper->MergeAllDummyLines();

	//절대 위치를 현재 위치로 치환한다.
	this->notepannel->paper->MoveToLocation(this->frontLineLocation, this->frontCharLocation, &frontLineOrder, &frontCharIndex);
	//붙일 내용을 붙인다. 
	this->notepannel->paper->Add(this->previousPaper, frontLineOrder, frontCharIndex);
	//현재 위치를 구한다. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//현재 위치를 마지막 위치로 지정하고 절대 위치를 구한다. 
	endLineOrder = lineOrder;
	endCharIndex = charIndex;
	this->notepannel->paper->GetLocation(endLineOrder, endCharIndex, &this->endLineLocation, &this->endCharLocation);
	//붙여 넣은 위치를 선택한다. 
	//delete this->notepannel->select;
	//this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);
	//현재 위치로 이동한다.
	lineOrder = this->notepannel->paper->Move(lineOrder);
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->Move(charIndex);

	//업데이트를 한다(위치, 내용 등)
	this->notepannel->hasChanged = TRUE;
	this->notepannel->documentUploaded = TRUE;
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//클라이언트를 갱신하다.
	this->notepannel->Invalidate(TRUE);
	//캐럿을 출력한다.
	this->notepannel->caret->ShowCaret();

}

/*
* 함수명칭:UnExecute
* 기능:복사하기 커멘드를 실행취소한다.
*/
void PasteCommand::UnExecute() {
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

	//업데이트를 한다(위치, 내용 등)
	this->notepannel->hasChanged = TRUE;
	this->notepannel->documentUploaded = TRUE;
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//클라이언트를 갱신하다.
	this->notepannel->Invalidate(TRUE);
	//캐럿을 출력한다.
	this->notepannel->caret->ShowCaret();
}