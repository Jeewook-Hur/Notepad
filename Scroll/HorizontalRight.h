//HorizontalRight.h
/*
* 파일명칭:HorizontalRight.h
* 기능:가로 스크롤의 액션중 오른쪽로 이동할 때의 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220929
*/
#ifndef _HORIZONTALRIGHT_H
#define _HORIZONTALRIGHT_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalRight : public HorizontalScrollAction {
public:
	HorizontalRight(Notepannel* notepannel);
	virtual ~HorizontalRight();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALRIGHT_H