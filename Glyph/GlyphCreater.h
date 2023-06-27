//GlyphCharacter.h
/*
* 파일명칭:GlyphCharacter.h
* 기능:문자 클래스를 생성하는 팩토리 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/8/23
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