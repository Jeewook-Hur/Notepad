//CharacterMatrix.cpp
/*
* ���ϸ�Ī:CharacterMatrix.cpp
* ���:������ Ư¡�� �����ϴ� ����
* �ۼ���:������
* �ۼ�����:2022/8/5
*/
#include "CharacterMatrix.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "ClientLocation.h"
#include "Notepannel.h"
#include "Font.h"
#include "Zoomer.h"

/*
* �Լ���Ī:CharacterMatrix
* ���:������
*/
CharacterMatrix::CharacterMatrix(Notepannel* notepannel) {
	this->notepannel = notepannel;
	this->widths = new int[129];
	CSize cSize = { 0, 0 };
	char ascii;
	CString temp;
	int asciiInt = 0;
	int i = 0;
	int tab;
	int space;

	CPaintDC cPaintDC(this->notepannel); //�ʺ� ���ϱ� ���� ����̽� ���ؽ�Ʈ�� �����.
	LOGFONT logFont;
	CFont cFont;
	CString fontName;
	BOOL italic;
	BOOL bold;
	int height;
	int boldInt = 400;

	//���� ������ �ý��� �⺻ �۲��� �����´�. 
	cPaintDC.GetCurrentFont()->GetLogFont(&logFont);

	//����۲ÿ� �°� �۲��� �����Ѵ�. 
	fontName = this->notepannel->font->name;
	height = this->notepannel->font->size * this->notepannel->zoomer->magnification / 100;
	italic = this->notepannel->font->italic;
	bold = this->notepannel->font->bold;
	if (bold == TRUE) {
		boldInt = 800;
	}
	cFont.CreateFontA(height, 0, logFont.lfEscapement, logFont.lfOrientation, bold,
		italic, logFont.lfUnderline, logFont.lfStrikeOut, logFont.lfCharSet, logFont.lfOutPrecision,
		logFont.lfClipPrecision, logFont.lfQuality, logFont.lfPitchAndFamily, fontName);

	//�ٲ� �۲��� ����̽� ���ؽ�Ʈ�� �����Ѵ�.
	cPaintDC.SelectObject(&cFont);

	//�ʺ� ��Ŀ� �ƽ�Ű �ڵ忡 �´� �ʺ� ã�� �ִ´�. 
	while (i < 128) {
		ascii = (char)asciiInt;
		asciiInt++;
		temp.Format("%c", ascii);
		cSize = cPaintDC.GetOutputTextExtent(temp, 1);
		this->widths[i] = cSize.cx;
		i++;
	}
	//�������Ʈ ũ�⿡ �´� �ʺ� 129��° �׸� �ִ´�.
	temp.Format("%s", "��");
	cSize = cPaintDC.GetOutputTextExtent(temp, 2); 
	this->widths[128] = cSize.cx;
	this->height = cSize.cy;
	//��Ű�� ũ�⸦ �缳���Ͽ� �ִ´�. 
	space = this->widths[' '];
	tab = space * 8;
	this->widths['\t'] = tab;

	this->averageWidth = logFont.lfWidth * 2;
}
CharacterMatrix::CharacterMatrix(const CharacterMatrix& source) {
	int i = 0;

	this->notepannel = source.notepannel;
	this->height = source.height;
	this->widths = new int[129];
	while (i < 129) {
		this->widths[i] = source.widths[i];
		i++;
	}
	this->averageWidth = source.averageWidth;
}

/*
* �Լ���Ī:CharacterMatrix
* ���:�Ҹ���
*/
CharacterMatrix::~CharacterMatrix() {
	delete[] this->widths;
}

/*
* �Լ���Ī:GetCharacterWidth
* ��� : �Է¹��� ������ ���� ���Ѵ�.
*/
int CharacterMatrix::GetCharacterWidth(Glyph * character) {
	string temp;
	int asciiOrder;
	int width = -1;
	SingleByteCharacter tab('\t');

	if (dynamic_cast<SingleByteCharacter*>(character)) {
#if 0 
		temp = character->GetString();
		asciiOrder = (int)(temp[0]);
		width = this->widths[asciiOrder];
#endif
		if (dynamic_cast<SingleByteCharacter*>(character)->IsNotEqual(tab)) {
			temp = character->GetString();
			asciiOrder = (int)(temp[0]);
			width = this->widths[asciiOrder];
		}
		else {
			width = this->widths['\t'];
		}
	}
	else if (dynamic_cast<DoubleByteCharacter*>(character)) {
		width = this->widths[128];
	}
	return width;
}
int CharacterMatrix::GetCharacterWidth(Glyph* line, int order) {
	Glyph* character;
	string temp;
	int asciiOrder;
	int width = -1;
	SingleByteCharacter tab('\t');

	character = line->GetAt(order);
	if (dynamic_cast<SingleByteCharacter*>(character)) {
#if 0
		temp = character->GetString();
		asciiOrder = (int)(temp[0]);
		width = this->widths[asciiOrder];
#endif
		if (dynamic_cast<SingleByteCharacter*>(character)->IsNotEqual(tab)) {
			temp = character->GetString();
			asciiOrder = (int)(temp[0]);
			width = this->widths[asciiOrder];
		}
		else {
			width = this->widths['\t'];
		}
	}
	else if (dynamic_cast<DoubleByteCharacter*>(character)) {
		width = this->widths[128];
	}
	return width;
}

/*
* �Լ���Ī:GetDoubleByteWidth
* ���:�������Ʈ ���� ���Ѵ�. 
*/
int CharacterMatrix::GetDoubleByteWidth() {
	return this->widths[128];
}

/*
* �Լ���Ī:GetLineWidth
* ���: �Է¹��� ���� �Է¹��� �������� ���� ���Ѵ�.
*/
int CharacterMatrix::GetLineWidth(Glyph* line) {
	//Glyph* character = 0;
	int characterWidth = -1;
	int widthSum = 0;
	int i = 0;

	while (i < line->GetLength()) {
		//character = line->GetAt(i);
		//characterWidth = this->GetCharacterWidth(character);
		characterWidth = this->GetCharacterWidth(line, i);
		widthSum += characterWidth;
		i++;
	}
	return widthSum;
}
int CharacterMatrix::GetLineWidth(Glyph* line, int current) {
	//Glyph* character = 0;
	int characterWidth = -1;
	int widthSum = 0;
	int i = 0;

	while (i <= current) {
		//character = line->GetAt(i);
		//characterWidth = this->GetCharacterWidth(character);
		characterWidth = this->GetCharacterWidth(line, i);

		widthSum += characterWidth;
		i++;
	}
	return widthSum;
}

/*
* �Լ���Ī:GetLineHeight
* ���:�Է¹��� �� ������ ���̸� ���Ѵ�.
*/
int CharacterMatrix::GetLineHeight(int lineOrder) {
	return this->height * lineOrder;
}

/*
* �Լ���Ī:FindNearWidthPosition
* ���:�Է¹��� �ٿ��� �Է¹��� ���� ����� ��ġ�� ã�� ��ȯ�Ѵ�.
*/
int CharacterMatrix::FindNearWidthPosition(Glyph* line, int widthCompare) {
	//Glyph* character = 0;
	int characterWidth = -1;
	int widthSum = 0;
	int order = -2;
	int i = 0;
	int interval;
	int lineLength = 0;

	if (widthCompare < 0) { //�Էµ� ���� �����̸� 0ó���Ѵ�.
		widthCompare = 0;
	}

	lineLength = line->GetLength();
	while (i < lineLength && widthSum <= widthCompare) {
		//character = line->GetAt(i);
		//characterWidth = this->GetCharacterWidth(character);
		characterWidth = this->GetCharacterWidth(line, i);
		widthSum += characterWidth;
		order++;
		i++;
	}
	if (order >= -1) { //�ٿ� ���� ������
		interval = widthSum - widthCompare;
		if (interval < (characterWidth / 2)) { //���� �߰��� �̻��̸�(����(interval)���̳ʽ� ���� ����)
			order++; //���� �ܾ ���Ѵ�. 
		}
	}
	else if (order < -1) { //�ٿ� ���� ������
		order = -1;
	}
	return order;
}

/*
* �Լ���Ī:FindNearWidthPositionDown
* ���:�Է¹��� �ٿ��� �Է¹��� ���� ����� ��ġ�� �������� ã�� ��ȯ�Ѵ�.
*/
int CharacterMatrix::FindNearWidthPositionDown(Glyph* line, int widthCompare) {
	//Glyph* character = 0;
	int characterWidth = -1;
	int widthSum = 0;
	int order = -2;
	int i = 0;
	int lineWidth;

	lineWidth = this->GetLineWidth(line);

	while (i < line->GetLength() && widthSum <= widthCompare) {
		//character = line->GetAt(i);
		//characterWidth = this->GetCharacterWidth(character);
		characterWidth = this->GetCharacterWidth(line, i);
		widthSum += characterWidth;
		order++;
		i++;
	}
	if (order < -1) {
		order = -1;
	}
	else if (widthCompare >= lineWidth) {
		order = line->GetLength() - 1;
	}
	return order;
}


/*
* �Լ���Ī:FindNearHeightPosition
* ���:
*/
int CharacterMatrix::FindNearHeightPosition(int heightCompare) { //���� Ŭ���̾�Ʈ ��ǥ�� �Է¹޴´�.
	int order;
	int currentLocation;
	int paperLength;
	int clientLineOrder;

	if (heightCompare < 0) { //�Էµ� ���� �����̸� 0���� ó���Ѵ�.
		heightCompare = 0;
	}

	//Ŭ���̾�Ʈ ��ǥ�� �´� Ŭ���̾�Ʈ���� �ټ��� ã�´�.
	order = heightCompare / (this->height); 
	//�Է��� ������ ������ ���� �ټ��� ã�´�.
	clientLineOrder = this->notepannel->clientLocation->lineOrder;
	currentLocation = order + clientLineOrder;
	paperLength = this->notepannel->paper->GetLength() - 1;
	if (currentLocation > paperLength) { //�����ټ��� ���� �� �� ���� ũ��
		//���� �ټ��� �����.
		currentLocation = paperLength;
	}
	//���� �����ټ����� Ŭ���̾�Ʈ �ټ��� ġȯ�Ѵ�.
	order = currentLocation - clientLineOrder;

	//��ũ�� ���� �� �Լ�����
	//if (order > this->notepannel->paper->GetLength() - 1) {
	//	order = this->notepannel->paper->GetLength() - 1;
	//}
	return order; //Ŭ���̾�Ʈ �� ���� ��ȯ�Ѵ�. 
}

#if 0
/*
* �Լ���Ī:CalculateTabWidth
* ���:���� ���� ���Ͽ� ����Ѵ�. 
*/
int CharacterMatrix::CalculateTabWidth(Glyph* line, int order) {
	int width = -1;
	int tabWidth = -1;
	int sum;

	width = this->GetLineWidth(line, order - 1);
	sum = width / (this->averageWidth * 8);
	tabWidth = ((sum + 1) * this->averageWidth * 8) - width;

	return tabWidth;
}
#endif