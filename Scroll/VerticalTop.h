//VerticalTop.h
/*
* 파일명칭:VerticalTop.h
* 기능:세로 스크롤의 액션중 위로 이동하는 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220928
*/
#ifndef _VERTICALTOP_H
#define _VERTICALTOP_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalTop : public VerticalScrollAction {
public:
	VerticalTop(Notepannel* notepannel);
	virtual ~VerticalTop();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALTOP_H