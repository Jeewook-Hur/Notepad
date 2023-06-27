//VerticalPageDown.h
/*
* ���ϸ�Ī:VerticalPageDown.h
* ���:���� ��ũ���� �׼��� �� ������ �Ʒ��� �̵��ϴ� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220928
*/
#ifndef _VERTICALPAGEDOWN_H
#define _VERTICALPAGEDOWN_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalPageDown : public VerticalScrollAction {
public:
	VerticalPageDown(Notepannel* notepannel);
	virtual ~VerticalPageDown();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALPAGEDOWN_H