//LineWrapper.h
/*
* 파일명칭:LineWrapper.h
* 기능:입력받은 종이를 자동개행하고 위치를 보존하는 함수의 헤더
* 작성자:허지욱
* 작성일자:2022/12/19
*/
#ifndef _LINEWRAPPER_H
#define _LINEWRAPPER_H

class Notepannel;
class Glyph;
class LineWrapper {
public:
	LineWrapper(Notepannel* notepannel);
	~LineWrapper();
	void Warp(Glyph* paper, int width);
	void UnWarp(Glyph* paper);
private:
	Notepannel* notepannel;
};

#endif // !_LINEWRAPPER_H

