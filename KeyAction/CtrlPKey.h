//CtrlPKey.h
/*
* ���ϸ�Ī:CtrlPKey.h
* ���:ctrl�� PŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/12/19
*/
#ifndef _CTRLPKEY_H
#define _CTRLPKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlPKey :public KeyAction {
public:
	CtrlPKey(Notepannel* notepannel);
	virtual ~CtrlPKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLPKEY_H
