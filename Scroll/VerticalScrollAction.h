//VerticalScrollAction.h
/*
* 파일명칭:VerticalScrollAction.h
* 기능:세로스크롤 액션의 가상함수 헤더
* 작성자:허지욱
* 작성일자:20220928
*/
#ifndef _VERTICALSCROLLACTION_H
#define _VERTICALSCROLLACTION_H

typedef unsigned int UINT;
class CScrollBar;
class VerticalScrollAction {
public:
	VerticalScrollAction();
	virtual ~VerticalScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) = 0;
};

#endif // !_VERTICALSCROLLACTION_H
