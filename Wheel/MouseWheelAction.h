//MouseWheelAction.h
/*
* 파일명칭:MouseWheelAction.h
* 기능:마우스 휠 액션 가상함수의 헤더
* 작성자:허지욱
* 작성일자:2022/10/12
*/
#ifndef _MOUSEWHEELACTION_H
#define _MOUSEWHEELACTION_H

typedef int BOOL;
typedef unsigned int UINT;
class CPoint;
class MouseWheelAction {
public:
	MouseWheelAction();
	virtual ~MouseWheelAction() = 0;
	virtual BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) = 0;
};

#endif// !_MOUSEWHEELACTION_H