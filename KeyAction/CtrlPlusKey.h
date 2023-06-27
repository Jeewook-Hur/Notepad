//CtrlPlusKey.h
/*
* ���ϸ�Ī:CtrlPlusKey.h
* ���:ctrl�� +Ű�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _CTRLPLUSKEY_H
#define _CTRLPLUSKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlPlusKey :public KeyAction {
public:
	CtrlPlusKey(Notepannel* notepannel);
	virtual ~CtrlPlusKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLPLUSKEY_H
