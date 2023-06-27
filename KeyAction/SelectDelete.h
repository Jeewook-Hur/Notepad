//SelectDelete.h
/*
* ���ϸ�Ī:SelectDelete.h
* ���:���ÿ����� ���ﶧ�� Ű�׼� ���
* �ۼ���:������
* �ۼ�����:2022/11/15
*/
#ifndef _SELECTDELETE_H
#define _SELECTDELETE_H
#include "KeyAction.h"

class Notepannel;

class SelectDelete :public KeyAction {
public:
	SelectDelete(Notepannel* notepannel);
	virtual ~SelectDelete();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SELECTDELETE_H
