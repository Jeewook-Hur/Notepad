//PaintVisitor.cpp
/*
* 파일명칭:PaintVisitor.cpp
* 기능:클라이언트에 출력하는 콘크리트 비지터 클래스
* 작성자:허지욱
* 작성일자:2022/11/8
*/
#include "PaintVisitor.h"
#include "Notepannel.h"
#include "Font.h"
#include "CharacterMatrix.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Select.h"
#include "DocumentVirtualSize.h"

#include "Glyph.h"
#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"

/*
* 함수명칭:PaintVisitor
* 기능:생성자
*/
PaintVisitor::PaintVisitor(Notepannel* notepannel, CDC* cPaintDC) :notepannel(notepannel), cPaintDC(cPaintDC) {
	this->lineOrder = this->notepannel->clientLocation->lineOrder;
	this->charOrder = 0;
	this->currentLineWidth = 0;
}

/*
* 함수명칭:~PaintVisitor
* 기능:소멸자
*/
PaintVisitor::~PaintVisitor() {
}

/*
* 함수명칭:VisitPaint
* 기능:Paper클래스를 Visite하는 함수
*/
void PaintVisitor::Visit(Paper* paper) {
	Glyph* currentLine = NULL;
	int length;
	int clientLineNumber;
	int i = this->lineOrder;
	int j = 0;

	clientLineNumber = this->notepannel->clientMatrix->lineNumberInPage + 1;
	length = paper->GetLength();
	while (i < length && j < clientLineNumber) {
		currentLine = paper->GetAt(this->lineOrder);
		this->charOrder = 0;
		this->currentLineWidth = 0;
		currentLine->Accept(this);
		this->lineOrder++;
		i++;
		j++;
	}
}

/*
* 함수명칭:VisitLine
* 기능:Line클래스를 Visite하는 함수
*/
void PaintVisitor::Visit(Line* line) {
	Glyph* character = NULL;
	int length;
	int i = 0;
	int charWidth; 
	int clientLeft = this->notepannel->clientLocation->x - this->notepannel->characterMatrix->averageWidth * 2;
	int clientRight = clientLeft + this->notepannel->clientMatrix->width + this->notepannel->characterMatrix->averageWidth * 2;

	length = line->GetLength();
	while (i < length) {
		character = line->GetAt(this->charOrder);
		if (this->currentLineWidth >= clientLeft && this->currentLineWidth <= clientRight) {
			character->Accept(this);
		}
		charWidth = this->notepannel->characterMatrix->GetCharacterWidth(character);
		this->currentLineWidth = this->currentLineWidth + charWidth;
		this->charOrder++;
		i++;
	}
}

/*
* 함수명칭:VisitDummyLine
* 기능:DummyLine클래스를 Visite하는 함수
*/
void PaintVisitor::Visit(DummyLine* dummyLine) {
	Glyph* character = NULL;
	int length;
	int i = 0;
	int charWidth;
	int clientLeft = this->notepannel->clientLocation->x - this->notepannel->characterMatrix->averageWidth * 2;
	int clientRight = clientLeft + this->notepannel->clientMatrix->width + this->notepannel->characterMatrix->averageWidth * 2;

	length = dummyLine->GetLength();
	while (i < length) {
		character = dummyLine->GetAt(this->charOrder);
		if (this->currentLineWidth >= clientLeft && this->currentLineWidth <= clientRight) {
			character->Accept(this);
		}
		charWidth = this->notepannel->characterMatrix->GetCharacterWidth(character);
		this->currentLineWidth = this->currentLineWidth + charWidth;
		this->charOrder++;
		i++;
	}
}

/*
* 함수명칭:VisitSingleByteCharacter
* 기능:SingleByteCharacter클래스를 Visite하는 함수
*/
void PaintVisitor::Visit(SingleByteCharacter* singleByteCharacter) {
	BOOL isSelected = FALSE;
	//하이라이트 부분
	//블루 FF0000 
	//소프트 블루 72B1FB(rgb)->FBB172(hex)
	//스카이 블루 0x00FFBF00(hex)
	//장미 레드 D30505 -> 0505D3
	//보라 #800080 -> 800080
	//COLORREF rgbBlue = 0x00FFBF00;
	//빨주노초파남보
	COLORREF rgbWhite = 0x00FFFFFF;
	COLORREF rgbBlack = 0x00000000;
	COLORREF rgbRed = 0x000505D3;
	COLORREF rgbOrange = 0x000066FF;
	COLORREF rgbYello = 0x0054E0FF;
	COLORREF rgbGreen = 0x0006B644;
	COLORREF rgbBlue = 0x00FBB172; // 0505D3;//FBB172;//FFBF00;
	COLORREF rgbIndigo = 0x0078462E;
	COLORREF rgbPurple = 0x00800080;

	//int clientSeven = this->notepannel->clientMatrix->width / 7;
	//int number = (this->currentLineWidth - this->notepannel->clientLocation->x) / clientSeven;
	

	//위치의 글자가 선택되었는지 확인한다.
	isSelected = this->notepannel->select->IsSelected(this->lineOrder, this->charOrder);
	if (this->notepannel->isSelected == TRUE && isSelected == TRUE) { //
#if 0
		if (number == 0) { this->cPaintDC->SetBkColor(rgbRed); }
		else if (number == 1) { this->cPaintDC->SetBkColor(rgbOrange);}
		else if (number == 2) { this->cPaintDC->SetBkColor(rgbYello);}
		else if (number == 3) { this->cPaintDC->SetBkColor(rgbGreen);}
		else if (number == 4) { this->cPaintDC->SetBkColor(rgbBlue);}
		else if (number == 5) { this->cPaintDC->SetBkColor(rgbIndigo);}
		else if (number == 6) { this->cPaintDC->SetBkColor(rgbPurple);}
#endif
		this->cPaintDC->SetBkColor(rgbBlue);
		this->cPaintDC->SetTextColor(rgbWhite);
	}
	else {
		this->cPaintDC->SetBkColor(rgbWhite);
		this->cPaintDC->SetTextColor(rgbBlack);
	}
	this->cPaintDC->TextOutA(this->currentLineWidth - this->notepannel->clientLocation->x, this->notepannel->characterMatrix->height * (this->lineOrder - this->notepannel->clientLocation->lineOrder), singleByteCharacter->GetString().c_str()); //빈칸을 출력한다. 
}

/*
* 함수명칭:VisitDoubleByteCharacter
* 기능:DoubleByteCharacter클래스를 Visite하는 함수
*/
void PaintVisitor::Visit(DoubleByteCharacter* doubleByteCharacter) {
	BOOL isSelected = FALSE;
	//하이라이트 부분
	//블루 FF0000 
	//소프트 블루 72B1FB(rgb)->FBB172(hex)
	//스카이 블루 0x00FFBF00(hex)
	//COLORREF rgbBlue = 0x00FFBF00;
	COLORREF rgbWhite = 0x00FFFFFF;
	COLORREF rgbBlack = 0x00000000;
	COLORREF rgbRed = 0x000505D3;
	COLORREF rgbOrange = 0x000066FF;
	COLORREF rgbYello = 0x0054E0FF;
	COLORREF rgbGreen = 0x0006B644;
	COLORREF rgbBlue = 0x00FBB172; // 0505D3;//FBB172;//FFBF00;
	COLORREF rgbIndigo = 0x0078462E;
	COLORREF rgbPurple = 0x00800080;

	//int clientSeven = this->notepannel->clientMatrix->width / 7;
	//int number = (this->currentLineWidth - this->notepannel->clientLocation->x) / clientSeven;

	//위치의 글자가 선택되었는지 확인한다.
	isSelected = this->notepannel->select->IsSelected(this->lineOrder, this->charOrder);
	if (this->notepannel->isSelected == TRUE && isSelected == TRUE) {
#if 0
		if (number == 0) { this->cPaintDC->SetBkColor(rgbRed); }
		else if (number == 1) { this->cPaintDC->SetBkColor(rgbOrange); }
		else if (number == 2) { this->cPaintDC->SetBkColor(rgbYello); }
		else if (number == 3) { this->cPaintDC->SetBkColor(rgbGreen); }
		else if (number == 4) { this->cPaintDC->SetBkColor(rgbBlue); }
		else if (number == 5) { this->cPaintDC->SetBkColor(rgbIndigo); }
		else if (number == 6) { this->cPaintDC->SetBkColor(rgbPurple); }
#endif
		this->cPaintDC->SetBkColor(rgbBlue);
		this->cPaintDC->SetTextColor(rgbWhite);
	}
	else {
		this->cPaintDC->SetBkColor(rgbWhite);
		this->cPaintDC->SetTextColor(rgbBlack);
	}
	this->cPaintDC->TextOutA(this->currentLineWidth - this->notepannel->clientLocation->x, this->notepannel->characterMatrix->height * (this->lineOrder - this->notepannel->clientLocation->lineOrder), doubleByteCharacter->GetString().c_str()); //빈칸을 출력한다. 
}

