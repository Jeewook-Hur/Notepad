//CtrlMinusKey.h
/*
* ���ϸ�Ī:CtrlMinusKey.h
* ���:ctrl�� -Ű�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _CTRLMINUSKEY_H
#define _CTRLMINUSKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlMinusKey :public KeyAction {
public:
	CtrlMinusKey(Notepannel* notepannel);
	virtual ~CtrlMinusKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLMINUSKEY_H
