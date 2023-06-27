//CtrlWheelUp.h
/*
* ���ϸ�Ī:CtrlWheelUp.h
* ���:��Ʈ���� �������¿��� ���콺 ���� ���� ���������� �̺�Ʈ�� �����ϴ� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/10/12
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
