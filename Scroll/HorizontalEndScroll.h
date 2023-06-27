//HorizontalEndScroll.h
/*
* 파일명칭:HorizontalEndScroll.h
* 기능:가로 스크롤의 액션중 오른쪽 끝으로 이동할 때의 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220929
*/
#ifndef _HORIZONTALENDSCROLL_H
#define _HORIZONTALENDSCROLL_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalEndScroll : public HorizontalScrollAction {
public:
	HorizontalEndScroll(Notepannel* notepannel);
	virtual ~HorizontalEndScroll();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALENDSCROLL_H