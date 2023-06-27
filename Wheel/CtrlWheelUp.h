//CtrlWheelUp.h
/*
* 파일명칭:CtrlWheelUp.h
* 기능:컨트롤을 누른상태에서 마우스 휠을 위로 굴렸을때의 이벤트를 수행하는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/10/12
*/
#ifndef _CTRLWHEELUP_H
#define _CTRLWHEELUP_H
#include "MouseWheelAction.h"

typedef int BOOL;
typedef unsigned int UINT;
class CPoint;
class Notepannel;
class CtrlWheelUp : public MouseWheelAction {
public:
	CtrlWheelUp(Notepannel* notepannel);
	virtual ~CtrlWheelUp();
	virtual BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLWHEELUP_H
