//MouseWheelActionCreator.h
/*
* ���ϸ�Ī:MouseWheelActionCreator.h
* ���:���콺 �� �׼� ���� ���丮�� ���
* �ۼ���:������
* �ۼ�����:2022/10/12
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
