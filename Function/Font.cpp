//Font.cpp
/*
* 파일명칭:Font.cpp
* 기능:폰트 클래스
* 작성자:허지욱
* 작성일자:2022/8/3
*/
#include "Font.h"

/*
* 함수명칭:Font
* 기능:생성자
*/
Font::Font() {
	this->name = "굴림";
	this->size = 36;
	this->bold = FALSE;
	this->italic = FALSE;
}
Font::Font(CString name, int size){
	this->name = name;
	this->size = size;
	this->bold = FALSE;
	this->italic = FALSE;
}
Font::Font(CString name, int size, BOOL bold, BOOL italic) {
	this->name = name;
	this->size = size;
	this->bold = bold;
	this->italic = italic;
}
Font::Font(LOGFONT logFont) : name(logFont.lfFaceName) {
	if (logFont.lfHeight > 0) {
		this->size = logFont.lfHeight;
	}
	else {
		this->size = -1 * logFont.lfHeight;
	}
	this->italic = logFont.lfItalic;
	if (logFont.lfWeight >= 600) {
		this->bold = TRUE;
	}
	else {
		this->bold = FALSE;
	}
}
Font::Font(const Font& source) {
	this->name = source.name;
	this->size = source.size;
	this->bold = source.bold;
	this->italic = source.italic;
}

/*
* 함수명칭:~Font
* 기능:소멸자
*/
Font::~Font() {
}
