//ShiftLeftKey.h
/*
* ���ϸ�Ī:ShiftLeftKey.h
* ���:shift�� ���� ȭ��ǥ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#ifndef _SHIFTLEFTKEY_H
#define _SHIFTLEFTKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftLeftKey :public KeyAction {
public:
	ShiftLeftKey(Notepannel* notepannel);
	virtual ~ShiftLeftKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTLEFTKEY_H
