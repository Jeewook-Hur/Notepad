//Scroll.h
/*
* 파일명칭:Scroll.h
* 기능:스크롤의 정보를 갱신하는 함수의 헤더
* 작성자:허지욱
* 작성일자:20220929
*/
#ifndef _SCROLL_H
#define _SCROLL_H

typedef unsigned int UINT;
class Notepannel;
class Scroll {
public:
	Scroll(Notepannel* notepannel);
	~Scroll();
	void Move(int x, int lineOrder);
	//void MoveToClientLocation();
	UINT pageSizeX;
	UINT pageSizeY;
	int maxX;
	int maxY;
private:
	Notepannel* notepannel;
};

#endif // !_SCROLL_H
