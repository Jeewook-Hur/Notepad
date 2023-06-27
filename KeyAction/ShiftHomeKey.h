//ShiftHomeKey.h
/*
* ���ϸ�Ī:ShiftHomeKey.h
* ���:shift�� ȨŰ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#ifndef _SHIFTHOMEKEY_H
#define _SHIFTHOMEKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftHomeKey :public KeyAction {
public:
	ShiftHomeKey(Notepannel* notepannel);
	virtual ~ShiftHomeKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTHOMEKEY_H
