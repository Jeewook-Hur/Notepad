//CharacterMatrix.cpp
/*
* 파일명칭:CharacterMatrix.cpp
* 기능:글자의 특징을 저장하는 파일
* 작성자:허지욱
* 작성일자:2022/8/5
*/
#include "CharacterMatrix.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "ClientLocation.h"
#include "Notepannel.h"
#include "Font.h"
#include "Zoomer.h"

/*
* 함수명칭:CharacterMatrix
* 기능:생성자
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

	CPaintDC cPaintDC(this->notepannel); //너비를 구하기 위한 디바이스 컨텍스트를 만든다.
	LOGFONT logFont;
	CFont cFont;
	CString fontName;
	BOOL italic;
	BOOL bold;
	int height;
	int boldInt = 400;

	//현재 설정된 시스템 기본 글꼴을 가져온다. 
	cPaintDC.GetCurrentFont()->GetLogFont(&logFont);

	//현재글꼴에 맞게 글꼴을 설정한다. 
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

	//바꾼 글꼴을 디바이스 컨텍스트에 갱신한다.
	cPaintDC.SelectObject(&cFont);

	//너비 행렬에 아스키 코드에 맞는 너비를 찾아 넣는다. 
	while (i < 128) {
		ascii = (char)asciiInt;
		asciiInt++;
		temp.Format("%c", ascii);
		cSize = cPaintDC.GetOutputTextExtent(temp, 1);
		this->widths[i] = cSize.cx;
		i++;
	}
	//더블바이트 크기에 맞는 너비를 129번째 항목에 넣는다.
	temp.Format("%s", "가");
	cSize = cPaintDC.GetOutputTextExtent(temp, 2); 
	this->widths[128] = cSize.cx;
	this->height = cSize.cy;
	//탭키의 크기를 재설정하여 넣는다. 
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
* 함수명칭:CharacterMatrix
* 기능:소멸자
*/
CharacterMatrix::~CharacterMatrix() {
	delete[] this->widths;
}

/*
* 함수명칭:GetCharacterWidth
* 기능 : 입력받은 글자의 폭을 구한다.
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
* 함수명칭:GetDoubleByteWidth
* 기능:더블바이트 폭을 구한다. 
*/
int CharacterMatrix::GetDoubleByteWidth() {
	return this->widths[128];
}

/*
* 함수명칭:GetLineWidth
* 기능: 입력받은 줄의 입력받은 값까지의 폭을 구한다.
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
* 함수명칭:GetLineHeight
* 기능:입력받은 줄 까지의 높이를 구한다.
*/
int CharacterMatrix::GetLineHeight(int lineOrder) {
	return this->height * lineOrder;
}

/*
* 함수명칭:FindNearWidthPosition
* 기능:입력받은 줄에서 입력받은 폭과 가까운 위치를 찾아 반환한다.
*/
int CharacterMatrix::FindNearWidthPosition(Glyph* line, int widthCompare) {
	//Glyph* character = 0;
	int characterWidth = -1;
	int widthSum = 0;
	int order = -2;
	int i = 0;
	int interval;
	int lineLength = 0;

	if (widthCompare < 0) { //입력된 폭이 음수이면 0처리한다.
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
	if (order >= -1) { //줄에 값이 있을대
		interval = widthSum - widthCompare;
		if (interval < (characterWidth / 2)) { //글자 중간점 이상이면(간격(interval)마이너스 값도 상정)
			order++; //다음 단어를 택한다. 
		}
	}
	else if (order < -1) { //줄에 값이 없을때
		order = -1;
	}
	return order;
}

/*
* 함수명칭:FindNearWidthPositionDown
* 기능:입력받은 줄에서 입력받은 폭과 가까운 위치중 작은쪽을 찾아 반환한다.
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
* 함수명칭:FindNearHeightPosition
* 기능:
*/
int CharacterMatrix::FindNearHeightPosition(int heightCompare) { //높이 클라이언트 좌표를 입력받는다.
	int order;
	int currentLocation;
	int paperLength;
	int clientLineOrder;

	if (heightCompare < 0) { //입력된 값이 음수이면 0으로 처리한다.
		heightCompare = 0;
	}

	//클라이언트 좌표에 맞는 클라이언트에서 줄수를 찾는다.
	order = heightCompare / (this->height); 
	//입력한 높이의 문서상 가상 줄수를 찾는다.
	clientLineOrder = this->notepannel->clientLocation->lineOrder;
	currentLocation = order + clientLineOrder;
	paperLength = this->notepannel->paper->GetLength() - 1;
	if (currentLocation > paperLength) { //가상줄수가 실제 줄 수 보다 크면
		//실제 줄수에 맞춘다.
		currentLocation = paperLength;
	}
	//구한 가상줄수에서 클라이언트 줄수로 치환한다.
	order = currentLocation - clientLineOrder;

	//스크롤 쓰기 전 함수내용
	//if (order > this->notepannel->paper->GetLength() - 1) {
	//	order = this->notepannel->paper->GetLength() - 1;
	//}
	return order; //클라이언트 줄 수를 반환한다. 
}

#if 0
/*
* 함수명칭:CalculateTabWidth
* 기능:탭의 폭을 구하여 출력한다. 
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