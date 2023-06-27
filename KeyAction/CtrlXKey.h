//CtrlXKey.h
/*
* ���ϸ�Ī:CtrlXKey.h
* ���:ctrl�� XŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _CTRLXKEY_H
#define _CTRLXKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlXKey :public KeyAction {
public:
	CtrlXKey(Notepannel* notepannel);
	virtual ~CtrlXKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLXKEY_H
