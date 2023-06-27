//Font.h
/*
* 파일명칭:Font.h
* 기능:폰트클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/8/3
*/
#ifndef _FONT_H
#define _FONT_H
#include <afxwin.h>

class Font {
public:
	Font();
	Font(CString name, int size);
	Font(CString name, int size, BOOL bold, BOOL italic);
	Font(LOGFONT logFont);
	Font(const Font& source);
	~Font();
	CString name;
	int size;
	BOOL bold;
	BOOL italic;
};

#endif _FONT_H