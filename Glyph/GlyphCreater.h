//GlyphCharacter.h
/*
* ���ϸ�Ī:GlyphCharacter.h
* ���:���� Ŭ������ �����ϴ� ���丮 Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/8/23
*/
#ifndef _GLYPHCREATER_H
#define _GLYPHCREATER_H
#include<string>
using namespace std;

class Glyph;
class GlyphCreater {
public:
	GlyphCreater();
	~GlyphCreater();
	static Glyph* Create(const char(*contents));
	Glyph* Create(string contents);
};

#endif // !_GLYPHCREATER_H