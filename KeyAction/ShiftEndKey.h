//ShiftEndKey.h
/*
* ���ϸ�Ī:ShiftEndKey.h
* ���:shift�� ����Ű�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#ifndef _SHIFTENDKEY_H
#define _SHIFTENDKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftEndKey :public KeyAction {
public:
	ShiftEndKey(Notepannel* notepannel);
	virtual ~ShiftEndKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTENDKEY_H
#pragma once
