//CtrlVKey.h
/*
* ���ϸ�Ī:CtrlVKey.h
* ���:ctrl�� VŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _CTRLVKEY_H
#define _CTRLVKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlVKey :public KeyAction {
public:
	CtrlVKey(Notepannel* notepannel);
	virtual ~CtrlVKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLVKEY_H
