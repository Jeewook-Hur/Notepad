//ShiftDownKey.h
/*
* ���ϸ�Ī:ShiftDownKey.h
* ���:shift�� �Ʒ��� ȭ��ǥ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#ifndef _SHIFTDOWNKEY_H
#define _SHIFTDOWNKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftDownKey :public KeyAction {
public:
	ShiftDownKey(Notepannel* notepannel);
	virtual ~ShiftDownKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTDOWNKEY_H
