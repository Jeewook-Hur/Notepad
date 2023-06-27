//VerticalBottom.h
/*
* 파일명칭:VerticalBottom.h
* 기능:세로 스크롤의 액션중 아래로 이동하는 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220928
*/
#ifndef _VERTICALBOTTOM_H
#define _VERTICALBOTTOM_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalBottom : public VerticalScrollAction {
public:
	VerticalBottom(Notepannel* notepannel);
	virtual ~VerticalBottom();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALBOTTOM_H