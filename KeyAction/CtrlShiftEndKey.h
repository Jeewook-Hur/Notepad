//CtrlShiftEndKey.h
/*
* ���ϸ�Ī:CtrlShiftEndKey.h
* ���:ctrlŰ�� shiftŰ�� ����Ű�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#ifndef _CTRLSHIFTENDKEY_H
#define _CTRLSHIFTENDKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftEndKey :public KeyAction {
public:
	CtrlShiftEndKey(Notepannel* notepannel);
	virtual ~CtrlShiftEndKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHIFTENDKEY_H
