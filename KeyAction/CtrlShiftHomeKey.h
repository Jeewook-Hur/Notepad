//CtrlShiftHomeKey.h
/*
* ���ϸ�Ī:CtrlShiftHomeKey.h
* ���:ctrlŰ�� shiftŰ�� ȨŰ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#ifndef _CTRLSHIFTHOMEKEY_H
#define _CTRLSHIFTHOMEKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftHomeKey :public KeyAction {
public:
	CtrlShiftHomeKey(Notepannel* notepannel);
	virtual ~CtrlShiftHomeKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHIFTHOMEKEY_H
