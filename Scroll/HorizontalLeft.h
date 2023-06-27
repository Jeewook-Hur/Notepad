//HorizontalLeft.h
/*
* 파일명칭:HorizontalLeft.h
* 기능:가로 스크롤의 액션중 왼쪽으로 이동할 때의 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220929
*/
#ifndef _HORIZONTALLEFT_H
#define _HORIZONTALLEFT_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalLeft : public HorizontalScrollAction {
public:
	HorizontalLeft(Notepannel* notepannel);
	virtual ~HorizontalLeft();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALLEFT_H