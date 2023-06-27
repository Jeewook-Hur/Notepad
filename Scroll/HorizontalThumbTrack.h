//HorizontalThumbTrack.h
/*
* 파일명칭:HorizontalThumbTrack.h
* 기능:가로 스크롤의 액션중 끌때의 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220929
*/
#ifndef _HORIZONTALTHUMBTRACK_H
#define _HORIZONTALTHUMBTRACK_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalThumbTrack : public HorizontalScrollAction {
public:
	HorizontalThumbTrack(Notepannel* notepannel);
	virtual ~HorizontalThumbTrack();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALTHUMBTRACK_H