//CtrlWKey.h
/*
* ���ϸ�Ī:CtrlWKey.h
* ���:ctrl�� WŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _CTRLWKEY_H
#define _CTRLWKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlWKey :public KeyAction {
public:
	CtrlWKey(Notepannel* notepannel);
	virtual ~CtrlWKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLWKEY_H
