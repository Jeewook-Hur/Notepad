//HorizontalPageLeft.h
/*
* 파일명칭:HorizontalPageLeft.h
* 기능:가로 스크롤의 액션중 한 페이지 왼쪽으로 이동할 때의 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220929
*/
#ifndef _HORIZONTALPAGELEFT_H
#define _HORIZONTALPAGELEFT_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalPageLeft : public HorizontalScrollAction {
public:
	HorizontalPageLeft(Notepannel* notepannel);
	virtual ~HorizontalPageLeft();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALPAGELEFT_H