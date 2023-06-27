//MouseWheelActionCreator.h
/*
* 파일명칭:MouseWheelActionCreator.h
* 기능:마우스 휠 액션 생성 팩토리의 헤더
* 작성자:허지욱
* 작성일자:2022/10/12
*/
#ifndef _MOUSEWHEELACTIONCREATOR_H
#define _MOUSEWHEELACTIONCREATOR_H

typedef unsigned int UINT;
class CPoint;
class Notepannel;
class MouseWheelAction;
class MouseWheelActionCreator {
public:
	MouseWheelActionCreator(Notepannel* notepannel);
	~MouseWheelActionCreator();
	MouseWheelAction* Create(UINT nFlags, short zDelta, CPoint pt);
private:
	Notepannel* notepannel;
};

#endif // !_MOUSEWHEELACTIONCREATOR_H
