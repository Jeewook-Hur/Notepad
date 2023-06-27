//VerticalThumbPosition.h
/*
* ���ϸ�Ī:VerticalThumbPosition.h
* ���:���� ��ũ���� �׼��� �������� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220928
*/
#ifndef _VERTICALTHUMBPOSITION_H
#define _VERTICALTHUMBPOSITION_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalThumbPosition : public VerticalScrollAction {
public:
	VerticalThumbPosition(Notepannel* notepannel);
	virtual ~VerticalThumbPosition();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALTHUMBPOSITION_H