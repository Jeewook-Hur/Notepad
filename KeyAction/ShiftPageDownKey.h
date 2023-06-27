//ShiftPageDownKey.h
/*
* ���ϸ�Ī:ShiftPageDownKey.h
* ���:shift�� PgDnŰ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#ifndef _SHIFTPAGEDOWNKEY_H
#define _SHIFTPAGEDOWNKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftPageDownKey :public KeyAction {
public:
	ShiftPageDownKey(Notepannel* notepannel);
	virtual ~ShiftPageDownKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTPAGEDOWNKEY_H
