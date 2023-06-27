//WheelDown.h
/*
* ���ϸ�Ī:WheelDown.h
* ���:���콺 ���� �Ʒ��� ���������� �̺�Ʈ�� �����ϴ� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/10/12
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
