//OnIDECharCommand.cpp
/*
* 파일명칭:OnIDECharCommand.cpp
* 기능:더블바이트 입력을 하는 커멘드
* 작성자:허지욱
* 작성일자:2022/11/29
*/
#include "OnIDECharCommand.h"
#include "Notepannel.h"
#include "Select.h"

#include "GlyphCreater.h"
#include "Paper.h"
#include "Line.h"

/*
* 함수명칭:OnIDECharCommand
* 기능:생성자
*/
OnIDECharCommand::OnIDECharCommand(Notepannel* notepannel, WPARAM wParam, LPARAM lParam) : notepannel(notepannel) {
	this->character = 0;
	this->lineLocation = -1;
	this->charLocation = -2;
	
	GlyphCreater glyphCreater;
	Glyph* currentLine;
	Long lineOrder;
	Long charIndex;
	char letter[3];
	//입력된 문자를 읽는다.
	letter[0] = HIBYTE(wParam);
	letter[1] = LOBYTE(wParam);
	letter[2] = '\0';

	//입력한 글자에 맞는 더블바이트 문자를 만든다. 
	this->character = glyphCreater.Create(letter);
	//종이의 현재 위치를 읽는다.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//현재위치를 토대로 절대 위치를 기억한다. 
	this->notepannel->paper->GetLocation(lineOrder, charIndex, &this->lineLocation, &this->charLocation);
}

/*
* 함수명칭:~OnIDECharCommand
* 기능:소멸자
*/
OnIDECharCommand::~OnIDECharCommand() {
	delete this->character;
}

/*
* 함수명칭:Execute
* 기능:커멘드를 실행한다.
*/
void OnIDECharCommand::Execute() {
	Glyph* currentLine = NULL;
	Glyph* clone = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;

	//종이의 더미줄을 병합한다.
	this->notepannel->paper->MergeAllDummyLines();

	//절대 위치로 현재위치를 찾는다. 
	this->notepannel->paper->MoveToLocation(this->lineLocation, this->charLocation, &lineOrder, &charIndex);

	currentLine = this->notepannel->paper->GetAt(lineOrder);

	//현재 위치에 글자를 입력한다. 
	currentLine->Add(this->character->Clone());
	
}

/*
* 함수명칭:UnExecute
* 기능:커멘드를 실행취소한다.
*/
void OnIDECharCommand::UnExecute() {
	Glyph* currentLine = NULL;
	Glyph* nextLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;

	//종이의 더미줄을 병합한다.
	this->notepannel->paper->MergeAllDummyLines();

	//절대 위치로 현재위치를 찾는다. 
	this->notepannel->paper->MoveToLocation(this->lineLocation, this->charLocation, &lineOrder, &charIndex);

	currentLine = this->notepannel->paper->GetAt(lineOrder);
	//입력한 위치의 글자를 지운다. 
	currentLine->Remove(charIndex + 1);

	
	if (this->notepannel->isSelected == TRUE) {//이전에 선택되었으면 선택된 영역을 해제한다. 
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel);
	}
	else { //선택하지 않았어도 디폴트로 선택해제해준다.
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel);
	}
	
}