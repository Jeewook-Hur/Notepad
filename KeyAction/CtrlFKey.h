//CtrlFKey.h
/*
* ���ϸ�Ī:CtrlFKey.h
* ���:ctrl�� FŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/12/7
*/
#ifndef _CTRLFKEY_H
#define _CTRLFKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlFKey :public KeyAction {
public:
	CtrlFKey(Notepannel* notepannel);
	virtual ~CtrlFKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLFKEY_H
