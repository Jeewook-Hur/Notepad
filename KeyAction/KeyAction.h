//KeyAction.h
/*
* ���ϸ�Ī:KeyAction.h
* ���:Ű�׼� �����Լ��� ���
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#ifndef _KEYACTION_H
#define _KEYACTION_H

typedef unsigned int UINT;
class KeyAction {
public:
	KeyAction();
	virtual ~KeyAction() = 0;
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
};

#endif// !_KEYACTION_H