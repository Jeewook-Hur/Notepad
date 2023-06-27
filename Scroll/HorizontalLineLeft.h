//HorizontalLineLeft.h
/*
* 파일명칭:HorizontalLineLeft.h
* 기능:가로 스크롤의 액션중 왼쪽으로 한 줄 이동할 때의 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220928
*/
#ifndef _HORIZONTALLINELEFT_H
#define _HORIZONTALLINELEFT_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalLineLeft : public HorizontalScrollAction {
public:
	HorizontalLineLeft(Notepannel* notepannel);
	virtual ~HorizontalLineLeft();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALLINELEFT_H