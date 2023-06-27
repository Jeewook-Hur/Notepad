//VerticalLineUp.h
/*
* 파일명칭:VerticalLineUp.h
* 기능:세로 스크롤의 액션중 한 줄 위로 이동하는 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220928
*/
#ifndef _VERTICALLINEUP_H
#define _VERTICALLINEUP_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalLineUp : public VerticalScrollAction {
public:
	VerticalLineUp(Notepannel* notepannel);
	virtual ~VerticalLineUp();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALLINEUP_H