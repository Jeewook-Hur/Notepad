//VerticalBottom.h
/*
* ���ϸ�Ī:VerticalBottom.h
* ���:���� ��ũ���� �׼��� �Ʒ��� �̵��ϴ� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220928
*/
#ifndef _VERTICALBOTTOM_H
#define _VERTICALBOTTOM_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalBottom : public VerticalScrollAction {
public:
	VerticalBottom(Notepannel* notepannel);
	virtual ~VerticalBottom();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALBOTTOM_H