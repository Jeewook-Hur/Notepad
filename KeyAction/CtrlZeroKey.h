//CtrlZeroKey.h
/*
* ���ϸ�Ī:CtrlZeroKey.h
* ���:ctrl�� 0Ű�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _CTRLZEROKEY_H
#define _CTRLZEROKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlZeroKey :public KeyAction {
public:
	CtrlZeroKey(Notepannel* notepannel);
	virtual ~CtrlZeroKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLZEROKEY_H
