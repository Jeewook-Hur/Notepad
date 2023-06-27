//CtrlShiftSKey.h
/*
* ���ϸ�Ī:CtrlShiftSKey.h
* ���:ctrl�� shift�� SŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _CTRLSHFITSKEY_H
#define _CTRLSHFITSKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftSKey :public KeyAction {
public:
	CtrlShiftSKey(Notepannel* notepannel);
	virtual ~CtrlShiftSKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHFITSKEY_H
