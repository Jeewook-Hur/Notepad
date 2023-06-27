//PrintVisitor.cpp
/*
* ���ϸ�Ī:PrintVisitor.cpp
* ���:����Ʈ������ ����ϴ� ��ũ��Ʈ ������ Ŭ����
* �ۼ���:������
* �ۼ�����:2022/12/16
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
* �Լ���Ī:PrintVisitor
* ���:������
*/
PrintVisitor::PrintVisitor(PreviewPage* previewPage, Notepannel* notepannel, CDC* cPaintDC) 
	:previewPage(previewPage), notepannel(notepannel), cPaintDC(cPaintDC) {
	this->lineOrder = 0;
	this->charOrder = 0;
	this->currentLineWidth = 0;
	this->currentPageNumber = 0;
}

/*
* �Լ���Ī:~PrintVisitor
* ���:�Ҹ���
*/
PrintVisitor::~PrintVisitor() {
}

/*
* �Լ���Ī:VisitPaint
* ���:PaperŬ������ Visite�ϴ� �Լ�
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
* �Լ���Ī:VisitLine
* ���:LineŬ������ Visite�ϴ� �Լ�
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
* �Լ���Ī:VisitDummyLine
* ���:DummyLineŬ������ Visite�ϴ� �Լ�
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
* �Լ���Ī:VisitSingleByteCharacter
* ���:SingleByteCharacterŬ������ Visite�ϴ� �Լ�
*/
void PrintVisitor::Visit(SingleByteCharacter* singleByteCharacter) {
	COLORREF rgbWhite = 0x00FFFFFF;
	COLORREF rgbBlack = 0x00000000;
	

	this->cPaintDC->SetBkColor(rgbWhite);
	this->cPaintDC->SetTextColor(rgbBlack);

	int outputlineOrder = this->lineOrder - ((this->previewPage->currentPage - 1) * this->previewPage->lineNumberInPage);
	this->cPaintDC->TextOutA(this->previewPage->marginLeftStart + this->currentLineWidth + 5, this->previewPage->headerPoint + (this->previewPage->textHeigth * outputlineOrder) + 5, singleByteCharacter->GetString().c_str()); //��ĭ�� ����Ѵ�. 
}

/*
* �Լ���Ī:VisitDoubleByteCharacter
* ���:DoubleByteCharacterŬ������ Visite�ϴ� �Լ�
*/
void PrintVisitor::Visit(DoubleByteCharacter* doubleByteCharacter) {
	COLORREF rgbWhite = 0x00FFFFFF;
	COLORREF rgbBlack = 0x00000000;

	this->cPaintDC->SetBkColor(rgbWhite);
	this->cPaintDC->SetTextColor(rgbBlack);

	int outputlineOrder = this->lineOrder - ((this->previewPage->currentPage - 1) * this->previewPage->lineNumberInPage);
	this->cPaintDC->TextOutA(this->previewPage->marginLeftStart + this->currentLineWidth + 5, this->previewPage->headerPoint + (this->previewPage->textHeigth * outputlineOrder) + 5, doubleByteCharacter->GetString().c_str()); //��ĭ�� ����Ѵ�. 
}
