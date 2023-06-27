//OnCharCommand.cpp
/*
* 파일명칭:OnCharCommand.cpp
* 기능:싱글바이트를 입력 하는 커멘드
* 작성자:허지욱
* 작성일자:2022/11/29
*/
#include "OnCharCommand.h"
#include "Notepannel.h"
#include "Select.h"
#include "CommandCreator.h"
#include "MacroCommand.h"

#include "GlyphCreater.h"
#include "Paper.h"
#include "Line.h"
#include "resource.h"

/*
* 함수명칭:OnCharCommand
* 기능:생성자
*/
OnCharCommand::OnCharCommand(Notepannel* notepannel, UINT nChar, UINT nRepCnt, UINT nFlags) : notepannel(notepannel) {
	this->character = 0;
	this->lineLocation = -1;
	this->charLocation = -2;

	GlyphCreater glyphCreater;
	Glyph* currentLine;
	Long lineOrder;
	Long charIndex;
	char charArray[2];
	charArray[0] = nChar;
	charArray[1] = '\0';

	//선택되었으면 선택된 영역을 지운다. 
	CommandCreator commandCreator(this->notepannel);
	Command* command = 0;
	if (this->notepannel->isSelected == TRUE) {
		command = commandCreator.Create(IDM_FORMAT_DELETE);
		command->Execute();
		this->notepannel->macroCommand->Add(command);
	}

	if (nChar != VK_RETURN) { //엔터키가 아니면 문자에 맞는 글자를 만든다. 
		this->character = glyphCreater.Create(charArray);
	}
	else {
		this->character = 0;
	}
	//종이의 현재 위치를 읽는다.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//현재위치를 토대로 절대 위치를 기억한다. 
	this->notepannel->paper->GetLocation(lineOrder, charIndex, &this->lineLocation, &this->charLocation);
}

/*
* 함수명칭:~OnCharCommand
* 기능:소멸자
*/
OnCharCommand::~OnCharCommand() {
	delete this->character;
}

/*
* 함수명칭:Execute
* 기능:커멘드를 실행한다.
*/
void OnCharCommand::Execute() {
	Glyph* currentLine = NULL;
	Glyph* clone = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;

	//종이의 더미줄을 병합한다.
	this->notepannel->paper->MergeAllDummyLines();

	//절대 위치로 현재위치를 찾는다. 
	this->notepannel->paper->MoveToLocation(this->lineLocation, this->charLocation, &lineOrder, &charIndex);
	
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	if (this->character != 0) {//엔터키가 아니면
		//현재 위치에 글자를 입력한다. 
		currentLine->Add(this->character->Clone());
	}
	else { //엔터키면
		//현재 줄의 클론을 만든다. 
		clone = currentLine->Clone();
		//클론의 맨 앞으부터 현재 위치까지 지운다. 
		clone->Remove(0, charIndex);
		//클론을 다음줄로 넣는다. 
		this->notepannel->paper->Add(lineOrder + 1, clone);
		//현재 줄의 현재 위치부터 줄의 끝까지 지운다. 
		currentLine->Remove(charIndex + 1, currentLine->GetLength() - 1);
		//종이에서 다음줄로 이동한다.
		lineOrder = this->notepannel->paper->Move(lineOrder + 1);
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		//다음 줄에서 맨 앞으로 이동한다.
		currentLine->First();
	}
}

/*
* 함수명칭:UnExecute
* 기능:커멘드를 실행취소한다.
*/
void OnCharCommand::UnExecute() {
	Glyph* currentLine = NULL;
	Glyph* nextLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long charOrder = -1;

	//종이의 더미줄을 병합한다.
	this->notepannel->paper->MergeAllDummyLines();

	//절대 위치로 현재위치를 찾는다. 
	this->notepannel->paper->MoveToLocation(this->lineLocation, this->charLocation, &lineOrder, &charIndex);
	
	//원래 글자의 순서를 입력한다.
	charOrder = charIndex + 1;

	currentLine = this->notepannel->paper->GetAt(lineOrder);
	if (this->character != 0) {//엔터키가 아니면
		//입력한 위치의 글자를 지운다. 
		currentLine->Remove(charOrder);
	}
	else { //엔터키면
		//입력한 위치의 줄을 가져온다.
		//입력한 위치 다음의 줄을 가져온다.
		nextLine = this->notepannel->paper->GetAt(lineOrder + 1);
		//입력한 위치의 줄에 다음 줄을 더한다.
		currentLine->Add(nextLine, charOrder);
		//다음 줄을 지운다.
		this->notepannel->paper->Remove(lineOrder + 1);
		//현재위치로 이동한다.
		lineOrder = this->notepannel->paper->Move(lineOrder);
		currentLine->Move(charIndex);
	}


	if (this->notepannel->isSelected == TRUE) {//이전에 선택되었으면 선택된 영역을 해제한다. 
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel);
	}
	else { //선택하지 않았어도 디폴트로 선택해제해준다.
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel);
	}

}