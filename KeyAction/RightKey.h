//RightKey.h
/*
* ���ϸ�Ī:RightKey.h
* ���:������ ȭ��ǥ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#ifndef _RIGTHKEY_H
#define _RIGTHKEY_H
#include "KeyAction.h"

class Notepannel;

class RightKey :public KeyAction {
public:
	RightKey(Notepannel* notepannel);
	virtual ~RightKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_RIGTHKEY_H
