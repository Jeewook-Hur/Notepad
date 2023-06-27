//HorizontalLineLeft.h
/*
* ���ϸ�Ī:HorizontalLineLeft.h
* ���:���� ��ũ���� �׼��� �������� �� �� �̵��� ���� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220928
*/
#ifndef _HORIZONTALLINELEFT_H
#define _HORIZONTALLINELEFT_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalLineLeft : public HorizontalScrollAction {
public:
	HorizontalLineLeft(Notepannel* notepannel);
	virtual ~HorizontalLineLeft();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALLINELEFT_H