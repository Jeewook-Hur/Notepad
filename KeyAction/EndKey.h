//EndKey.h
/*
* ���ϸ�Ī:EndKey.h
* ���:����Ű�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#ifndef _ENDKEY_H
#define _ENDKEY_H
#include "KeyAction.h"

class Notepannel;

class EndKey :public KeyAction {
public:
	EndKey(Notepannel* notepannel);
	virtual ~EndKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_ENDKEY_H
