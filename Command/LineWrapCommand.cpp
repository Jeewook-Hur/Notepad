//LineWrapCommand.cpp
/*
* 파일명칭:LineWrapCommand.cpp
* 기능:자동 줄 바꿈 메뉴
* 작성자:허지욱
* 작성일자:20220920
*/
#include "LineWrapCommand.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "DocumentVirtualSize.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Scroll.h"
#include "Select.h"
#include "LineWrapper.h"

#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include<string>
using namespace std;



/*
* 함수명칭:LineWrapCommand
* 기능:생성자
*/
LineWrapCommand::LineWrapCommand(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* 함수명칭:LineWrapCommand
* 기능:소멸자
*/
LineWrapCommand::~LineWrapCommand() {
}

/*
* 함수명칭:Execute
* 기능:자동 줄 바꿈 커멘드를 실행한다.
*/
void LineWrapCommand::Execute() {
	Long widthToCut = -1;


#if 0
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
	Long widthToCut = -1;
	Long index = -2;
	Long i = 0;

	Long frontLineLocation;
	Long frontCharLocation;
	Long frontLineOrder = this->notepannel->select->frontLineOrder;
	Long frontCharIndex = this->notepannel->select->frontXIndex;
	Long endLineLocation;
	Long endCharLocation;
	Long endLineOrder = this->notepannel->select->endLineOrder;
	Long endCharIndex = this->notepannel->select->endXIndex;

	//종이에서 현재 줄의 위치와 현재 줄에서의 현재 위치를 기억한다.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLineRemember = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLineRemember->GetCurrent();
	currentLineOrder = lineOrder;
	currentCharIndex = charIndex;
	this->notepannel->paper->GetLocation(currentLineOrder, currentCharIndex, &lineLocation, &charLocation);
	if (this->notepannel->isSelected == TRUE) { //선택되었으면
		this->notepannel->paper->GetLocation(frontLineOrder, frontCharIndex, &frontLineLocation, &frontCharLocation);
		this->notepannel->paper->GetLocation(endLineOrder, endCharIndex, &endLineLocation, &endCharLocation);
	}
	//종이에서 마지막 줄을 기억한다.
	lastOrder = this->notepannel->paper->Last();
	lastPage = this->notepannel->paper->GetAt(lastOrder);
	//종이에서 처음 줄로 이동한다.
	lineOrder = this->notepannel->paper->First();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	//윈도우의 너비를 구한다.
	widthToCut = this->notepannel->clientMatrix->width;
	//창의 크기가 너무 작을때를 대비한 최소치를 준비한다. 
	if (widthToCut < 120) {
		widthToCut = 120;
	}
	paperLength = this->notepannel->paper->GetLength();
	while (i < paperLength) {//종이의 길이만큼 반복한다.
		//현재 줄의 길이를 구한다.
		lineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine);
		//현재 줄의 길이가 창의 길이보다 크면 반복한다
		while (lineWidth > widthToCut) {
			//더미 줄에서 윈도우 너비와 가까운 내림 단어를 찾는다.
			index = this->notepannel->characterMatrix->FindNearWidthPositionDown(currentLine, widthToCut); //letterDown으로 바꾼다.
			//위치의 단어가 어떤 자료형인지 구분한다. 
			character = currentLine->GetAt(index);
			characterString = character->GetString();
			characterLetter = characterString[0];
			if (dynamic_cast<SingleByteCharacter*>(character)
				&& (characterLetter == 34 || characterLetter == 39 || (characterLetter >= 65 && characterLetter <= 90) || (characterLetter >= 97 && characterLetter <= 122))) { //위치의 단어가 영어이면
				//나눌 위치를 단어로 구분한다. 
				index = currentLine->Move(index);
				index = currentLine->PreviousWord();
				if (index <= -1) { //위치가 맨 앞이면 
					//더미 줄에서 윈도우 너비와 가까운 위치를 찾는다.
					index = this->notepannel->characterMatrix->FindNearWidthPositionDown(currentLine, widthToCut);
				}
			}
			//줄을 위치를 기준으로 더미줄로 나눈다. 
			dummyLineOrder = this->notepannel->paper->SplitDummyLine(lineOrder, index);
			//나눈 더미줄로 이동한다.
			lineOrder = dummyLineOrder;
			currentLine = this->notepannel->paper->GetAt(lineOrder);
			//현재 줄의 길이를 구한다. 
			lineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine);

		}
		//다음 줄로 이동한다.
		lineOrder = this->notepannel->paper->Next();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		i++;
	}
	//기억한 위치로 이동한다. 
	this->notepannel->paper->MoveToLocation(lineLocation, charLocation, &currentLineOrder, &currentCharIndex);
	currentLineOrder = this->notepannel->paper->Move(currentLineOrder);
	currentLine = this->notepannel->paper->GetAt(currentLineOrder);
	currentLine->Move(currentCharIndex);
	if (this->notepannel->isSelected == TRUE) { //선택되었으면
		this->notepannel->paper->MoveToLocation(frontLineLocation, frontCharLocation, &frontLineOrder, &frontCharIndex);
		this->notepannel->paper->MoveToLocation(endLineLocation, endCharLocation, &endLineOrder, &endCharIndex);

		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);
	}
#endif

	LineWrapper lineWrapper(this->notepannel);

	//윈도우의 너비를 구한다.
	widthToCut = this->notepannel->clientMatrix->width;
	//창의 크기가 너무 작을때를 대비한 최소치를 준비한다. 
	if (widthToCut < 80) {
		widthToCut = 80;
	}
	
	lineWrapper.Warp(this->notepannel->paper, widthToCut);

	if (this->notepannel->isCalledFromMenu == TRUE) { //메뉴에서 호출했을 경우 //개행 및 업데이트를 해야할 때
		//문서의 맨 앞으로 이동한다
		this->notepannel->paper->First();
		this->notepannel->paper->GetAt(0)->First();
		//개행처리중임을 표시한다. //LineWrapCommand 비 실행
		this->notepannel->isLineWraping = TRUE;
		//문서에서 내용의 업데이트를 했음을 표시한다. 
		this->notepannel->documentUploaded = TRUE;
		//스크롤 자동조정이 필요함을 표시한다.
		this->notepannel->clientMoveCheck = TRUE;
		//메모장의 업데이트를 호출한다.
		this->notepannel->Notify();
		//선택 클래스를 초기화한다.
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel);

		//클라이언트의 가상위치를 현재위치에 맞게 이동시킨다. 
		//this->notepannel->clientLocation->Move(0, 0);
		//this->notepannel->scroll->Move(0, 0);
		//클라이언트 화면을 갱신한다.
		this->notepannel->Invalidate(TRUE);
		//캐럿을 표시한다. 
		this->notepannel->caret->ShowCaret();
		this->notepannel->isCalledFromMenu = FALSE;
	}

	//스크롤을 비활성화 한다. 
	this->notepannel->EnableScrollBar(SB_HORZ, ESB_DISABLE_BOTH);


	//개행처리가 끝났음을 표시한다.
	this->notepannel->isLineWraping = FALSE;
}

/*
* 함수명칭:UnExecute
* 기능:자동 줄 바꿈 커멘드를 실행한다.
*/
void LineWrapCommand::UnExecute() {


#if 0
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
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLineRemember = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLineRemember->GetCurrent();
	currentLineOrder = lineOrder;
	currentCharIndex = charIndex;
	this->notepannel->paper->GetLocation(currentLineOrder, currentCharIndex, &lineLocation, &charLocation);
	if (this->notepannel->isSelected == TRUE) { //선택되었으면
		this->notepannel->paper->GetLocation(frontLineOrder, frontCharIndex, &frontLineLocation, &frontCharLocation);
		this->notepannel->paper->GetLocation(endLineOrder, endCharIndex, &endLineLocation, &endCharLocation);
	}
	//종이에서 모든 더미줄을 기존 줄에 합친다.
	this->notepannel->paper->MergeAllDummyLines();

	//기억한 위치로 이동한다. 
	this->notepannel->paper->MoveToLocation(lineLocation, charLocation, &currentLineOrder, &currentCharIndex);
	currentLineOrder = this->notepannel->paper->Move(currentLineOrder);
	currentLine = this->notepannel->paper->GetAt(currentLineOrder);
	currentLine->Move(currentCharIndex);
	if (this->notepannel->isSelected == TRUE) { //선택되었으면
		this->notepannel->paper->MoveToLocation(frontLineLocation, frontCharLocation, &frontLineOrder, &frontCharIndex);
		this->notepannel->paper->MoveToLocation(endLineLocation, endCharLocation, &endLineOrder, &endCharIndex);

		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);
	}

#endif

	LineWrapper lineWrapper(this->notepannel);

	lineWrapper.UnWarp(this->notepannel->paper);

	if (this->notepannel->isCalledFromMenu == TRUE) { //메뉴에서 호출했을 경우 //개행 및 업데이트를 해야할 때
		//문서의 맨 앞으로 이동한다
		this->notepannel->paper->First();
		this->notepannel->paper->GetAt(0)->First();
		//개행처리중임을 표시한다. //LineWrapCommand 비 실행
		this->notepannel->isLineWraping = TRUE;
		//문서에서 내용의 업데이트를 했음을 표시한다. 
		this->notepannel->documentUploaded = TRUE;
		//스크롤 자동조정이 필요함을 표시한다.
		this->notepannel->clientMoveCheck = TRUE;
		//메모장의 업데이트를 호출한다.
		this->notepannel->Notify();
		//선택 클래스를 초기화한다.
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel);

		//클라이언트 화면을 갱신한다.
		this->notepannel->Invalidate(TRUE);
		//캐럿을 표시한다. 
		this->notepannel->caret->ShowCaret();

		this->notepannel->isCalledFromMenu = FALSE;
	}

	//스크롤을 활성화 한다. 
	this->notepannel->EnableScrollBar(SB_HORZ, ESB_ENABLE_BOTH);

	//개행처리가 끝났음을 표시한다.
	this->notepannel->isLineWraping = FALSE;
}