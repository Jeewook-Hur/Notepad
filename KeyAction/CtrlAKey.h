//CtrlAKey.h
/*
* ���ϸ�Ī:CtrlAKey.h
* ���:ctrl�� AŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/15
*/
#ifndef _CTRLAKEY_H
#define _CTRLAKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlAKey :public KeyAction {
public:
	CtrlAKey(Notepannel* notepannel);
	virtual ~CtrlAKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLAKEY_H
