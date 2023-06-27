//VerticalLineDown.h
/*
* ���ϸ�Ī:VerticalLineDown.h
* ���:���� ��ũ���� �׼��� �� �� �Ʒ��� �̵��ϴ� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220928
*/
#ifndef _VERTICALLINEDOWN_H
#define _VERTICALLINEDOWN_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalLineDown : public VerticalScrollAction {
public:
	VerticalLineDown(Notepannel* notepannel);
	virtual ~VerticalLineDown();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALLINEDOWN_H