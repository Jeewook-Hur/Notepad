//CtrlNKey.h
/*
* ���ϸ�Ī:CtrlNKey.h
* ���:ctrl�� NŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _CTRLNKEY_H
#define _CTRLNKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlNKey :public KeyAction {
public:
	CtrlNKey(Notepannel* notepannel);
	virtual ~CtrlNKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLNKEY_H
