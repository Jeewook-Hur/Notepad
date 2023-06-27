//PrintVisitor.cpp
/*
* 파일명칭:PrintVisitor.cpp
* 기능:프리트용지에 출력하는 콘크리트 비지터 클래스
* 작성자:허지욱
* 작성일자:2022/12/16
*/
#include "PrintVisitor.h"
#include "PreviewPage.h"
#include "Notepannel.h"
#include "Font.h"
#include "CharacterMatrix.h"

#include "Glyph.h"
#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"

/*
* 함수명칭:PrintVisitor
* 기능:생성자
*/
PrintVisitor::PrintVisitor(PreviewPage* previewPage, Notepannel* notepannel, CDC* cPaintDC) 
	:previewPage(previewPage), notepannel(notepannel), cPaintDC(cPaintDC) {
	this->lineOrder = 0;
	this->charOrder = 0;
	this->currentLineWidth = 0;
	this->currentPageNumber = 0;
}

/*
* 함수명칭:~PrintVisitor
* 기능:소멸자
*/
PrintVisitor::~PrintVisitor() {
}

/*
* 함수명칭:VisitPaint
* 기능:Paper클래스를 Visite하는 함수
*/
void PrintVisitor::Visit(Paper* paper) {
	Glyph* currentLine = NULL;
	int length;
	int clientLineNumber;
	int i = this->lineOrder;
	int j = 0;

	clientLineNumber = this->previewPage->lineNumberInPage;
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
void PrintVisitor::Visit(Line* line) {
	Glyph* character = NULL;
	int length;
	int i = 0;
	int charWidth; 

	length = line->GetLength();
	while (i < length) {
		character = line->GetAt(this->charOrder);
		charWidth = this->cPaintDC->GetOutputTextExtent(character->GetString().c_str()).cx;
		//charWidth = this->notepannel->characterMatrix->GetCharacterWidth(character);
		character->Accept(this);
		this->currentLineWidth = this->currentLineWidth + charWidth;
		this->charOrder++;
		i++;
	}
}

/*
* 함수명칭:VisitDummyLine
* 기능:DummyLine클래스를 Visite하는 함수
*/
void PrintVisitor::Visit(DummyLine* dummyLine) {
	Glyph* character = NULL;
	int length;
	int i = 0;
	int charWidth;

	length = dummyLine->GetLength();
	while (i < length) {
		character = dummyLine->GetAt(this->charOrder);
		charWidth = this->cPaintDC->GetOutputTextExtent(character->GetString().c_str()).cx;
		//charWidth = this->notepannel->characterMatrix->GetCharacterWidth(character);
		character->Accept(this);
		this->currentLineWidth = this->currentLineWidth + charWidth;
		this->charOrder++;
		i++;
	}
}

/*
* 함수명칭:VisitSingleByteCharacter
* 기능:SingleByteCharacter클래스를 Visite하는 함수
*/
void PrintVisitor::Visit(SingleByteCharacter* singleByteCharacter) {
	COLORREF rgbWhite = 0x00FFFFFF;
	COLORREF rgbBlack = 0x00000000;
	

	this->cPaintDC->SetBkColor(rgbWhite);
	this->cPaintDC->SetTextColor(rgbBlack);

	int outputlineOrder = this->lineOrder - ((this->previewPage->currentPage - 1) * this->previewPage->lineNumberInPage);
	this->cPaintDC->TextOutA(this->previewPage->marginLeftStart + this->currentLineWidth + 5, this->previewPage->headerPoint + (this->previewPage->textHeigth * outputlineOrder) + 5, singleByteCharacter->GetString().c_str()); //빈칸을 출력한다. 
}

/*
* 함수명칭:VisitDoubleByteCharacter
* 기능:DoubleByteCharacter클래스를 Visite하는 함수
*/
void PrintVisitor::Visit(DoubleByteCharacter* doubleByteCharacter) {
	COLORREF rgbWhite = 0x00FFFFFF;
	COLORREF rgbBlack = 0x00000000;

	this->cPaintDC->SetBkColor(rgbWhite);
	this->cPaintDC->SetTextColor(rgbBlack);

	int outputlineOrder = this->lineOrder - ((this->previewPage->currentPage - 1) * this->previewPage->lineNumberInPage);
	this->cPaintDC->TextOutA(this->previewPage->marginLeftStart + this->currentLineWidth + 5, this->previewPage->headerPoint + (this->previewPage->textHeigth * outputlineOrder) + 5, doubleByteCharacter->GetString().c_str()); //빈칸을 출력한다. 
}
