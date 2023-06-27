//WheelUp.h
/*
* ���ϸ�Ī:WheelUp.h
* ���:���콺 ���� ���� ���������� �̺�Ʈ�� �����ϴ� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/10/12
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
