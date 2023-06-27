//WheelDown.h
/*
* 파일명칭:WheelDown.h
* 기능:마우스 휠을 아래로 굴렸을때의 이벤트를 수행하는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/10/12
*/
#ifndef _WHEELDOWN_H
#define _WHEELDOWN_H
#include "MouseWheelAction.h"

typedef int BOOL;
typedef unsigned int UINT;
class CPoint;
class Notepannel;
class WheelDown : public MouseWheelAction {
public:
	WheelDown(Notepannel* notepannel);
	virtual ~WheelDown();
	virtual BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
private:
	Notepannel* notepannel;
};

#endif // !_WHEELDOWN_H
