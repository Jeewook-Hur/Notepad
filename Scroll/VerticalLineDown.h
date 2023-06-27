//VerticalLineDown.h
/*
* 파일명칭:VerticalLineDown.h
* 기능:세로 스크롤의 액션중 한 줄 아래로 이동하는 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220928
*/
#ifndef _VERTICALLINEDOWN_H
#define _VERTICALLINEDOWN_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalLineDown : public VerticalScrollAction {
public:
	VerticalLineDown(Notepannel* notepannel);
	virtual ~VerticalLineDown();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALLINEDOWN_H