//VerticalPageDown.h
/*
* 파일명칭:VerticalPageDown.h
* 기능:세로 스크롤의 액션중 한 페이지 아래로 이동하는 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220928
*/
#ifndef _VERTICALPAGEDOWN_H
#define _VERTICALPAGEDOWN_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalPageDown : public VerticalScrollAction {
public:
	VerticalPageDown(Notepannel* notepannel);
	virtual ~VerticalPageDown();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALPAGEDOWN_H