//VerticalThumbPosition.h
/*
* 파일명칭:VerticalThumbPosition.h
* 기능:세로 스크롤의 액션중 끌고나서의 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220928
*/
#ifndef _VERTICALTHUMBPOSITION_H
#define _VERTICALTHUMBPOSITION_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalThumbPosition : public VerticalScrollAction {
public:
	VerticalThumbPosition(Notepannel* notepannel);
	virtual ~VerticalThumbPosition();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALTHUMBPOSITION_H