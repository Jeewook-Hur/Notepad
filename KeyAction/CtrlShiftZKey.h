//CtrlShiftZKey.h
/*
* ���ϸ�Ī:CtrlShiftZKey.h
* ���:ctrl�� shift�� ZŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/29
*/
#ifndef _CTRLSHIFTZKEY_H
#define _CTRLSHIFTZKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftZKey :public KeyAction {
public:
	CtrlShiftZKey(Notepannel* notepannel);
	virtual ~CtrlShiftZKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHIFTZKEY_H
