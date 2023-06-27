//CtrlOKey.h
/*
* ���ϸ�Ī:CtrlOKey.h
* ���:ctrl�� OŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _CTRLOKEY_H
#define _CTRLOKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlOKey :public KeyAction {
public:
	CtrlOKey(Notepannel* notepannel);
	virtual ~CtrlOKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLOKEY_H
