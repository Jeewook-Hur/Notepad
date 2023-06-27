//CtrlWheelDown.h
/*
* ���ϸ�Ī:CtrlWheelDown.h
* ���:��Ʈ���� �������¿��� ���콺 ���� �Ʒ��� ���������� �̺�Ʈ�� �����ϴ� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/10/12
*/
#ifndef _CTRLWHEELDOWN_H
#define _CTRLWHEELDOWN_H
#include "MouseWheelAction.h"

typedef int BOOL;
typedef unsigned int UINT;
class CPoint;
class Notepannel;
class CtrlWheelDown : public MouseWheelAction {
public:
	CtrlWheelDown(Notepannel* notepannel);
	virtual ~CtrlWheelDown();
	virtual BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLWHEELDOWN_H
