//VerticalPageUp.h
/*
* 파일명칭:VerticalPageUp.h
* 기능:세로 스크롤의 액션중 한 페이지 위로 이동하는 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220928
*/
#ifndef _VERTICALPAGEUP_H
#define _VERTICALPAGEUP_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalPageUp : public VerticalScrollAction {
public:
	VerticalPageUp(Notepannel* notepannel);
	virtual ~VerticalPageUp();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALPAGEUP_H