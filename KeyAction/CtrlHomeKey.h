//CtrlHomeKey.h
/*
* ���ϸ�Ī:CtrlHomeKey.h
* ���:��Ʈ�Ѱ� ȨŰ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#ifndef _CTRLHOMEKEY_H
#define _CTRLHOMEKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlHomeKey :public KeyAction {
public:
	CtrlHomeKey(Notepannel* notepannel);
	virtual ~CtrlHomeKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLHOMEKEY_H
