//ShiftKey.h
/*
* ���ϸ�Ī:ShiftKey.h
* ���:shiftŰ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/10/18
*/
#ifndef _SHIFTKEY_H
#define _SHIFTKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftKey :public KeyAction {
public:
	ShiftKey(Notepannel* notepannel);
	virtual ~ShiftKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTKEY_H
