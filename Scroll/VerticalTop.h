//VerticalTop.h
/*
* ���ϸ�Ī:VerticalTop.h
* ���:���� ��ũ���� �׼��� ���� �̵��ϴ� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220928
*/
#ifndef _VERTICALTOP_H
#define _VERTICALTOP_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalTop : public VerticalScrollAction {
public:
	VerticalTop(Notepannel* notepannel);
	virtual ~VerticalTop();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALTOP_H