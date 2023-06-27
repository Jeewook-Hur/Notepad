//Select.cpp
/*
* 파일명칭:Select.cpp
* 기능:선택하기에 관한 기능을 저장하는 클래스
* 작성자:허지욱
* 작성일자:20221014
*/
#include "Select.h"
#include "Notepannel.h"
#include "Paper.h"

/*
* 함수명칭:Select
* 기능:생성자
*/
Select::Select(Notepannel* notepannel, int previousXIndex, int previousLineOrder, int currentXIndex, int currentLineOrder):notepannel(notepannel) {
	//값 대입
	this->previousXIndex = previousXIndex;
	this->previousLineOrder = previousLineOrder;
	this->currentXIndex = currentXIndex;
	this->currentLineOrder = currentLineOrder;
	//크기에 따른 분류
	if (this->currentLineOrder > this->previousLineOrder) {
		this->frontXIndex = this->previousXIndex;
		this->frontLineOrder = this->previousLineOrder;
		this->endXIndex = this->currentXIndex;
		this->endLineOrder = this->currentLineOrder;
	}
	else if (this->currentLineOrder == this->previousLineOrder && this->currentXIndex >= this->previousXIndex) {
		this->frontXIndex = this->previousXIndex;
		this->frontLineOrder = this->previousLineOrder;
		this->endXIndex = this->currentXIndex;
		this->endLineOrder = this->currentLineOrder;
	}
	else {
		this->frontXIndex = this->currentXIndex;
		this->frontLineOrder = this->currentLineOrder;
		this->endXIndex = this->previousXIndex;
		this->endLineOrder = this->previousLineOrder;
	}

	if (!(this->frontLineOrder == this->endLineOrder && this->frontXIndex == this->endXIndex)) {
		this->notepannel->isSelected = TRUE;
	}

	if (this->frontLineOrder == this->endLineOrder && this->frontXIndex == this->endXIndex) {
		this->frontXIndex = -1;
		this->frontLineOrder = 0;
		this->endXIndex = -1;
		this->endLineOrder = 0;
		this->notepannel->isSelected = FALSE;
	}

}

/*
* 함수명칭:~Select
* 기능:소멸자
*/
Select::~Select() {
	this->notepannel->isSelected = FALSE;
}

/*
* 함수명칭:MoveCurrent
* 기능:입력받은 위치로 현재 위치를 옮긴다.
*/
void Select::MoveCurrent(int currentXIndex, int currentLineOrder) {
	//대입
	this->currentXIndex = currentXIndex;
	this->currentLineOrder = currentLineOrder;
	//크기에 따른 분류
	if (this->currentLineOrder > this->previousLineOrder) {
		this->frontXIndex = this->previousXIndex;
		this->frontLineOrder = this->previousLineOrder;
		this->endXIndex = this->currentXIndex;
		this->endLineOrder = this->currentLineOrder;
	}
	else if (this->currentLineOrder == this->previousLineOrder && this->currentXIndex >= this->previousXIndex) {
		this->frontXIndex = this->previousXIndex;
		this->frontLineOrder = this->previousLineOrder;
		this->endXIndex = this->currentXIndex;
		this->endLineOrder = this->currentLineOrder;
	}
	else {
		this->frontXIndex = this->currentXIndex;
		this->frontLineOrder = this->currentLineOrder;
		this->endXIndex = this->previousXIndex;
		this->endLineOrder = this->previousLineOrder;
	}

	if (!(this->frontLineOrder == this->endLineOrder && this->frontXIndex == this->endXIndex)) {
		this->notepannel->isSelected = TRUE;
	}


}

/*
* 함수명칭:IsSelected
* 기능:범위를 입력하면 선택되었는지 확인한다.
*/
BOOL Select::IsSelected(int lineOrder, int charOrder) {
	BOOL ret = FALSE;


	if (lineOrder == this->frontLineOrder && lineOrder != this->endLineOrder && charOrder > this->frontXIndex) { //선택한 영역의 맨앞줄이면
		ret = TRUE;
	}
	else if (lineOrder > this->frontLineOrder && lineOrder < this->endLineOrder) { //선택한 영역의 중간줄이면
		ret = TRUE;
	}
	else if (lineOrder != frontLineOrder && lineOrder == this->endLineOrder && charOrder <= this->endXIndex) { //선택한 영역의 마지막 줄이면
		ret = TRUE;
	}
	else if (lineOrder == this->frontLineOrder && lineOrder == this->endLineOrder && charOrder > this->frontXIndex && charOrder <= this->endXIndex) { //선택영역이 한줄이면
		ret = TRUE;
	}
	return ret;
}


/*
* 함수명칭:IsEqual
* 기능:선택방은 위치가 입력받은 종이와 일치하는지 확인한다. 
*/
BOOL Select::IsEqual(Glyph* other) {
	BOOL ret = FALSE;
	Glyph* clone = 0;
	
	clone = this->notepannel->paper->Clone(this->frontLineOrder, this->frontXIndex, this->endLineOrder, this->endXIndex);
	if (clone->IsEqual(other)) {
		ret = TRUE;
	}

	delete clone;
	return ret;
}
