//VerticalEndScroll.h
/*
* 파일명칭:VerticalEndScroll.h
* 기능:세로 스크롤의 액션중 맨 아래로 이동하는 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220928
*/
#ifndef _VERTICALENDSCROLL_H
#define _VERTICALENDSCROLL_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalEndScroll : public VerticalScrollAction {
public:
	VerticalEndScroll(Notepannel* notepannel);
	virtual ~VerticalEndScroll();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALENDSCROLL_H