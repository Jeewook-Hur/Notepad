//ShiftRightKey.h
/*
* ���ϸ�Ī:ShiftRightKey.h
* ���:shift�� ������ ȭ��ǥ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#ifndef _SHIFTRIGHTKEY_H
#define _SHIFTRIGHTKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftRightKey :public KeyAction {
public:
	ShiftRightKey(Notepannel* notepannel);
	virtual ~ShiftRightKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTRIGHTKEY_H
