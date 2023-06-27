//DownKey.h
/*
* ���ϸ�Ī:DownKey.h
* ���:�Ʒ� ȭ��ǥ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#ifndef _DOWNKEY_H
#define _DOWNKEY_H
#include "KeyAction.h"

class Notepannel;

class DownKey :public KeyAction {
public:
	DownKey(Notepannel* notepannel);
	virtual ~DownKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_DOWNKEY_H
