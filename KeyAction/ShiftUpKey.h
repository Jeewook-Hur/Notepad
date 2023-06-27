//ShiftUpKey.h
/*
* ���ϸ�Ī:ShiftUpKey.h
* ���:shift�� ���� ȭ��ǥ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#ifndef _SHIFTUPKEY_H
#define _SHIFTUPKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftUpKey :public KeyAction {
public:
	ShiftUpKey(Notepannel* notepannel);
	virtual ~ShiftUpKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTUPKEY_H
