//DocumentVirtualSize.h
/*
* 파일명칭:DocumentVirtualSize.h
* 기능:클라이언트의 문자 크기로 인한 문서의 가상 크기를 구하는 헤더
* 작성자:허지욱
* 작성일자:20220923
*/
#ifndef _DOCUMENTVIRTUALSIZE_H
#define _DOCUMENTVIRTUALSIZE_H

class Glyph;
class Notepannel;
class DocumentVirtualSize {
public:
	DocumentVirtualSize(Notepannel* notepannel);
	~DocumentVirtualSize();
	int MaxX;
	int MaxY;
	int availableX;
	int availableLine; //이동 가능한 줄 수(개수)
private:
	Notepannel* notepannel;
};

#endif // !_DOCUMENTVIRTUALSIZE_H
