//HorizontalLineRight.h
/*
* 파일명칭:HorizontalLineRight.h
* 기능:가로 스크롤의 액션중 한줄 오른쪽로 이동할 때의 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220929
*/
#ifndef _HORIZONTALLINERIGHT_H
#define _HORIZONTALLINERIGHT_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalLineRight : public HorizontalScrollAction {
public:
	HorizontalLineRight(Notepannel* notepannel);
	virtual ~HorizontalLineRight();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALLINERIGHT_H