//HorizontalScrollActionCreator.h
/*
* 파일명칭:HorizontalScrollActionCreator.h
* 기능:가로스크롤 액션의 함수를 만드는 헤더
* 작성자:허지욱
* 작성일자:20220929
*/
#ifndef _HORIZONTALSCROLLACTIONCREATOR_H
#define _HORIZONTALSCROLLACTIONCREATOR_H

typedef unsigned int UINT;
class CScrollBar;
class Notepannel;
class HorizontalScrollAction;
class HorizontalScrollActionCreator {
public:
	HorizontalScrollActionCreator(Notepannel* notepannel);
	~HorizontalScrollActionCreator();
	HorizontalScrollAction* Create(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALSCROLLACTIONCREATOR_H
