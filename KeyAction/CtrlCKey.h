//CtrlCKey.h
/*
* ���ϸ�Ī:CtrlCKey.h
* ���:ctrl�� CŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _CTRLCKEY_H
#define _CTRLCKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlCKey :public KeyAction {
public:
	CtrlCKey(Notepannel* notepannel);
	virtual ~CtrlCKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLCKEY_H
