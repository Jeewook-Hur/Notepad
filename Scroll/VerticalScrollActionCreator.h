//VerticalScrollActionCreator.h
/*
* 파일명칭:VerticalScrollActionCreator.h
* 기능:세로스크롤 액션의 함수를 만드는 헤더
* 작성자:허지욱
* 작성일자:20220928
*/
#ifndef _VERTICALSCROLLACTIONCREATOR_H
#define _VERTICALSCROLLACTIONCREATOR_H

typedef unsigned int UINT;
class CScrollBar;
class Notepannel;
class VerticalScrollAction;
class VerticalScrollActionCreator {
public:
	VerticalScrollActionCreator(Notepannel* notepannel);
	~VerticalScrollActionCreator();
	VerticalScrollAction* Create(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALSCROLLACTIONCREATOR_H
