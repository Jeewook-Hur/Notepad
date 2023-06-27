//ShiftPageUpKey.h
/*
* ���ϸ�Ī:ShiftPageUpKey.h
* ���:shift�� ��������Ű�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#ifndef _SHIFTPAGEUPKEY_H
#define _SHIFTPAGEUPKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftPageUpKey :public KeyAction {
public:
	ShiftPageUpKey(Notepannel* notepannel);
	virtual ~ShiftPageUpKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTPAGEUPKEY_H
