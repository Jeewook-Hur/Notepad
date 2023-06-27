//VerticalThumbTrack.h
/*
* 파일명칭:VerticalThumbTrack.h
* 기능:세로 스크롤의 액션중 끌때의 이벤트를 수행하는 헤더
* 작성자:허지욱
* 작성일자:20220929
*/
#ifndef _VERTICALTHUMBTRACK_H
#define _VERTICALTHUMBTRACK_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalThumbTrack : public VerticalScrollAction {
public:
	VerticalThumbTrack(Notepannel* notepannel);
	virtual ~VerticalThumbTrack();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALTHUMBTRACK_H