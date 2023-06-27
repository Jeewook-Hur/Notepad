//Font.h
/*
* ���ϸ�Ī:Font.h
* ���:��ƮŬ������ ���
* �ۼ���:������
* �ۼ�����:2022/8/3
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