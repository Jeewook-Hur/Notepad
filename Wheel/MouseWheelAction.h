//MouseWheelAction.h
/*
* ���ϸ�Ī:MouseWheelAction.h
* ���:���콺 �� �׼� �����Լ��� ���
* �ۼ���:������
* �ۼ�����:2022/10/12
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