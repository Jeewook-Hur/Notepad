//CtrlZKey.h
/*
* ���ϸ�Ī:CtrlZKey.h
* ���:ctrl�� ZŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/29
*/
#ifndef _CTRLZKEY_H
#define _CTRLZKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlZKey :public KeyAction {
public:
	CtrlZKey(Notepannel* notepannel);
	virtual ~CtrlZKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLZKEY_H
