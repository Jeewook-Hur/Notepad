//LineWrapper.cpp
/*
* 파일명칭:LineWrapper.cpp
* 기능:입력받은 종이를 자동개행하고 위치를 보존하는 함수의 헤더
* 작성자:허지욱
* 작성일자:2022/12/19
*/
#include "LineWrapper.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "DocumentVirtualSize.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Scroll.h"
#include "Select.h"

#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include<string>
using namespace std;

/*
* 함수명칭:LineWrapper
* 기능:생성자
*/
LineWrapper::LineWrapper(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* 함수명칭:~LineWrapper
* 기능:소멸자
*/
LineWrapper::~LineWrapper() {
}

/*
* 함수명칭:Wrap
* 기능:입력받은 종이를 입력받은 폭의 값으로 개행한다. 
*/
void LineWrapper::Warp(Glyph* paper, int width) {
	Glyph* currentLine = NULL;
	Glyph* currentLineRemember = NULL;
	Glyph* lastPage = NULL;
	Glyph* character = NULL;
	string characterString;
	char characterLetter;
	Long currentLineOrder = -1;
	Long charIndex = -2;
	Long currentCharIndex = -2;
	Long lineLocation;
	Long charLocation;
	Long lastOrder = -1;
	Long lineOrder = -1;
	Long lineLength = -1;
	Long lineWidth = -1;
	Long paperLength = -1;
	Long dummyLineOrder = -1;
	Long widthToCut = width;
	Long index = -2;
	Long tempIndex = -2;
	Long i = 0;
	char checkTab = '\0';

	Long frontLineLocation;
	Long frontCharLocation;
	Long frontLineOrder = this->notepannel->select->frontLineOrder;
	Long frontCharIndex = this->notepannel->select->frontXIndex;
	Long endLineLocation;
	Long endCharLocation;
	Long endLineOrder = this->notepannel->select->endLineOrder;
	Long endCharIndex = this->notepannel->select->endXIndex;

	//종이에서 현재 줄의 위치와 현재 줄에서의 현재 위치를 기억한다.
	lineOrder = paper->GetCurrent();
	currentLineRemember = paper->GetAt(lineOrder);
	charIndex = currentLineRemember->GetCurrent();
	currentLineOrder = lineOrder;
	currentCharIndex = charIndex;
	paper->GetLocation(currentLineOrder, currentCharIndex, &lineLocation, &charLocation);
	if (this->notepannel->isSelected == TRUE) { //선택되었으면
		paper->GetLocation(frontLineOrder, frontCharIndex, &frontLineLocation, &frontCharLocation);
		paper->GetLocation(endLineOrder, endCharIndex, &endLineLocation, &endCharLocation);
	}
	//종이에서 마지막 줄을 기억한다.
	lastOrder = paper->Last();
	lastPage = paper->GetAt(lastOrder);
	//종이에서 처음 줄로 이동한다.
	lineOrder = paper->First();
	currentLine = paper->GetAt(lineOrder);
	
	paperLength = paper->GetLength();
	while (i < paperLength) {//종이의 길이만큼 반복한다.
		//현재 줄의 길이를 구한다.
		lineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine);
		//현재 줄의 길이가 창의 길이보다 크면 반복한다
		while (lineWidth > widthToCut) {
			//더미 줄에서 윈도우 너비와 가까운 내림 단어를 찾는다.
			index = this->notepannel->characterMatrix->FindNearWidthPositionDown(currentLine, widthToCut); //letterDown으로 바꾼다.
			
			if (index >= 0) { //나눌 단어가 있으면
				//위치의 단어가 어떤 자료형인지 구분한다. 
				character = currentLine->GetAt(index);
				characterString = character->GetString();
				characterLetter = characterString[0];

				tempIndex = index;
				if (dynamic_cast<SingleByteCharacter*>(character)
					&& (characterLetter == 34 || characterLetter == 39 || (characterLetter >= 65 && characterLetter <= 90) || (characterLetter >= 97 && characterLetter <= 122))) { //위치의 단어가 영어이면
					//나눌 위치를 단어로 구분한다. 
					index = currentLine->Move(index);
					index = currentLine->PreviousWord();

					if (index > -1) {
						checkTab = (currentLine->GetAt(index)->GetExactString())[0];
					}

					if (index <= -1) { //위치가 맨 앞이면 
						//더미 줄에서 윈도우 너비와 가까운 위치를 찾는다.
						index = this->notepannel->characterMatrix->FindNearWidthPositionDown(currentLine, widthToCut);
					}
					else if (checkTab != '\0' && checkTab == '\t') {
						index = tempIndex;
					}
				}
			}
			else if (index < 0) {
				//나눌 단어가 없으면 한 단어를 선택하고 단어에 상관없이 나눈다.
				index = 0;
			}
			//줄을 위치를 기준으로 더미줄로 나눈다. 
			dummyLineOrder = paper->SplitDummyLine(lineOrder, index);
			//나눈 더미줄로 이동한다.
			lineOrder = dummyLineOrder;
			currentLine = paper->GetAt(lineOrder);
			//현재 줄의 길이를 구한다. 
			lineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine);

		}
		//다음 줄로 이동한다.
		lineOrder = paper->Next();
		currentLine = paper->GetAt(lineOrder);
		i++;
	}
	//기억한 위치로 이동한다. 
	paper->MoveToLocation(lineLocation, charLocation, &currentLineOrder, &currentCharIndex);
	currentLineOrder = paper->Move(currentLineOrder);
	currentLine = paper->GetAt(currentLineOrder);
	currentLine->Move(currentCharIndex);
	if (this->notepannel->isSelected == TRUE) { //선택되었으면
		paper->MoveToLocation(frontLineLocation, frontCharLocation, &frontLineOrder, &frontCharIndex);
		paper->MoveToLocation(endLineLocation, endCharLocation, &endLineOrder, &endCharIndex);

		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);
	}
}

/*
* 함수명칭:UnWrap
* 기능:입력받은 종이를 개행취소한다.
*/
void LineWrapper::UnWarp(Glyph* paper) {
	Glyph* currentLine = NULL;
	Glyph* currentLineRemember = NULL;

	Long lineOrder = -1;
	Long currentIndex = -2;

	Long charIndex;
	Long currentLineOrder;
	Long currentCharIndex;
	Long lineLocation;
	Long charLocation;

	Long frontLineLocation;
	Long frontCharLocation;
	Long frontLineOrder = this->notepannel->select->frontLineOrder;
	Long frontCharIndex = this->notepannel->select->frontXIndex;
	Long endLineLocation;
	Long endCharLocation;
	Long endLineOrder = this->notepannel->select->endLineOrder;
	Long endCharIndex = this->notepannel->select->endXIndex;

	//종이에서 현재 줄의 위치와 현재 줄에서의 현재 위치를 기억한다.
	lineOrder = paper->GetCurrent();
	currentLineRemember = paper->GetAt(lineOrder);
	charIndex = currentLineRemember->GetCurrent();
	currentLineOrder = lineOrder;
	currentCharIndex = charIndex;
	paper->GetLocation(currentLineOrder, currentCharIndex, &lineLocation, &charLocation);
	if (this->notepannel->isSelected == TRUE) { //선택되었으면
		paper->GetLocation(frontLineOrder, frontCharIndex, &frontLineLocation, &frontCharLocation);
		paper->GetLocation(endLineOrder, endCharIndex, &endLineLocation, &endCharLocation);
	}
	//종이에서 모든 더미줄을 기존 줄에 합친다.
	paper->MergeAllDummyLines();

	//기억한 위치로 이동한다. 
	paper->MoveToLocation(lineLocation, charLocation, &currentLineOrder, &currentCharIndex);
	currentLineOrder = paper->Move(currentLineOrder);
	currentLine = paper->GetAt(currentLineOrder);
	currentLine->Move(currentCharIndex);
	if (this->notepannel->isSelected == TRUE) { //선택되었으면
		paper->MoveToLocation(frontLineLocation, frontCharLocation, &frontLineOrder, &frontCharIndex);
		paper->MoveToLocation(endLineLocation, endCharLocation, &endLineOrder, &endCharIndex);

		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);
	}





}