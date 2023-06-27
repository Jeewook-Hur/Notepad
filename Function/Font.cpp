//Font.cpp
/*
* ���ϸ�Ī:Font.cpp
* ���:��Ʈ Ŭ����
* �ۼ���:������
* �ۼ�����:2022/8/3
*/
#include "Font.h"

/*
* �Լ���Ī:Font
* ���:������
*/
Font::Font() {
	this->name = "����";
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
* �Լ���Ī:~Font
* ���:�Ҹ���
*/
Font::~Font() {
}
