//VerticalPageUp.h
/*
* ���ϸ�Ī:VerticalPageUp.h
* ���:���� ��ũ���� �׼��� �� ������ ���� �̵��ϴ� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220928
*/
#ifndef _VERTICALPAGEUP_H
#define _VERTICALPAGEUP_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalPageUp : public VerticalScrollAction {
public:
	VerticalPageUp(Notepannel* notepannel);
	virtual ~VerticalPageUp();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALPAGEUP_H