//F5Key.h
/*
* ���ϸ�Ī:F5Key.h
* ���:F5Ű�� ���������� ���
* �ۼ���:������
* �ۼ�����:2023/1/31
*/
#ifndef _F5KEY_H
#define _F5KEY_H
#include "KeyAction.h"

class Notepannel;

class F5Key :public KeyAction {
public:
	F5Key(Notepannel* notepannel);
	virtual ~F5Key();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_F5KEY_H
