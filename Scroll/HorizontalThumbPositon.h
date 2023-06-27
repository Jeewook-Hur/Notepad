//HorizontalThumbPositon.h
/*
* 파일명칭:HorizontalThumbPositon.h
* 기능:가로 스크롤의 액션중 절대위치 일때의 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220929
*/
#ifndef _HORIZONTALTHUMBPOSITION_H
#define _HORIZONTALTHUMBPOSITION_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalThumbPositon : public HorizontalScrollAction {
public:
	HorizontalThumbPositon(Notepannel* notepannel);
	virtual ~HorizontalThumbPositon();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALTHUMBPOSITION_H