//CtrlSKey.h
/*
* ���ϸ�Ī:CtrlSKey.h
* ���:ctrl�� SŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _CTRLSKEY_H
#define _CTRLSKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlSKey :public KeyAction {
public:
	CtrlSKey(Notepannel* notepannel);
	virtual ~CtrlSKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSKEY_H
