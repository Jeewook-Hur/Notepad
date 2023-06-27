//HorizontalScrollAction.h
/*
* 파일명칭:HorizontalScrollAction.h
* 기능:가로스크롤 액션의 가상함수 헤더
* 작성자:허지욱
* 작성일자:20220929
*/
#ifndef _HORIZONTALSCROLLACTION_H
#define _HORIZONTALSCROLLACTION_H

typedef unsigned int UINT;
class CScrollBar;
class HorizontalScrollAction {
public:
	HorizontalScrollAction();
	virtual ~HorizontalScrollAction();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) = 0;
};

#endif // !_HORIZONTALSCROLLACTION_H
