//BackspaceKey.h
/*
* ���ϸ�Ī:BackspaceKey.h
* ���:�齺���̽�Ű�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/9/16
*/
#ifndef _BACKSPACEKEY_H
#define _BACKSPACEKEY_H
#include "KeyAction.h"

class Notepannel;

class BackspaceKey :public KeyAction {
public:
	BackspaceKey(Notepannel* notepannel);
	virtual ~BackspaceKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_BACKSPACEKEY_H
