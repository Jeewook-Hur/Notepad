//WheelUp.h
/*
* 파일명칭:WheelUp.h
* 기능:마우스 휠을 위로 굴렸을때의 이벤트를 수행하는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/10/12
*/
#ifndef _WHEELUP_H
#define _WHEELUP_H
#include "MouseWheelAction.h"

typedef int BOOL;
typedef unsigned int UINT;
class CPoint;
class Notepannel;
class WheelUp : public MouseWheelAction {
public:
	WheelUp(Notepannel* notepannel);
	virtual ~WheelUp();
	virtual BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
private:
	Notepannel* notepannel;
};

#endif // !_WHEELUP_H
