//PaintVisitor.cpp
/*
* ���ϸ�Ī:PaintVisitor.cpp
* ���:Ŭ���̾�Ʈ�� ����ϴ� ��ũ��Ʈ ������ Ŭ����
* �ۼ���:������
* �ۼ�����:2022/11/8
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
* �Լ���Ī:PaintVisitor
* ���:������
*/
PaintVisitor::PaintVisitor(Notepannel* notepannel, CDC* cPaintDC) :notepannel(notepannel), cPaintDC(cPaintDC) {
	this->lineOrder = this->notepannel->clientLocation->lineOrder;
	this->charOrder = 0;
	this->currentLineWidth = 0;
}

/*
* �Լ���Ī:~PaintVisitor
* ���:�Ҹ���
*/
PaintVisitor::~PaintVisitor() {
}

/*
* �Լ���Ī:VisitPaint
* ���:PaperŬ������ Visite�ϴ� �Լ�
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
* �Լ���Ī:VisitLine
* ���:LineŬ������ Visite�ϴ� �Լ�
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
* �Լ���Ī:VisitDummyLine
* ���:DummyLineŬ������ Visite�ϴ� �Լ�
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
* �Լ���Ī:VisitSingleByteCharacter
* ���:SingleByteCharacterŬ������ Visite�ϴ� �Լ�
*/
void PaintVisitor::Visit(SingleByteCharacter* singleByteCharacter) {
	BOOL isSelected = FALSE;
	//���̶���Ʈ �κ�
	//��� FF0000 
	//����Ʈ ��� 72B1FB(rgb)->FBB172(hex)
	//��ī�� ��� 0x00FFBF00(hex)
	//��� ���� D30505 -> 0505D3
	//���� #800080 -> 800080
	//COLORREF rgbBlue = 0x00FFBF00;
	//���ֳ����ĳ���
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
	

	//��ġ�� ���ڰ� ���õǾ����� Ȯ���Ѵ�.
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
	this->cPaintDC->TextOutA(this->currentLineWidth - this->notepannel->clientLocation->x, this->notepannel->characterMatrix->height * (this->lineOrder - this->notepannel->clientLocation->lineOrder), singleByteCharacter->GetString().c_str()); //��ĭ�� ����Ѵ�. 
}

/*
* �Լ���Ī:VisitDoubleByteCharacter
* ���:DoubleByteCharacterŬ������ Visite�ϴ� �Լ�
*/
void PaintVisitor::Visit(DoubleByteCharacter* doubleByteCharacter) {
	BOOL isSelected = FALSE;
	//���̶���Ʈ �κ�
	//��� FF0000 
	//����Ʈ ��� 72B1FB(rgb)->FBB172(hex)
	//��ī�� ��� 0x00FFBF00(hex)
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

	//��ġ�� ���ڰ� ���õǾ����� Ȯ���Ѵ�.
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
	this->cPaintDC->TextOutA(this->currentLineWidth - this->notepannel->clientLocation->x, this->notepannel->characterMatrix->height * (this->lineOrder - this->notepannel->clientLocation->lineOrder), doubleByteCharacter->GetString().c_str()); //��ĭ�� ����Ѵ�. 
}

