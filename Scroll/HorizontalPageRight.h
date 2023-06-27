//HorizontalPageRight.h
/*
* 파일명칭:HorizontalPageRight.h
* 기능:가로 스크롤의 액션중 오른쪽로 한 줄 이동할 때의 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220929
*/
#ifndef _HORIZONTALPAGERIGHT_H
#define _HORIZONTALPAGERIGHT_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalPageRight : public HorizontalScrollAction {
public:
	HorizontalPageRight(Notepannel* notepannel);
	virtual ~HorizontalPageRight();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALPAGERIGHT_H