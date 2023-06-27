//CtrlGKey.h
/*
* ���ϸ�Ī:CtrlGKey.h
* ���:ctrl�� GŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _CTRLGKEY_H
#define _CTRLGKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlGKey :public KeyAction {
public:
	CtrlGKey(Notepannel* notepannel);
	virtual ~CtrlGKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLGKEY_H
