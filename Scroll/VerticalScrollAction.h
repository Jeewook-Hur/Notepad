//VerticalScrollAction.h
/*
* ���ϸ�Ī:VerticalScrollAction.h
* ���:���ν�ũ�� �׼��� �����Լ� ���
* �ۼ���:������
* �ۼ�����:20220928
*/
#ifndef _VERTICALSCROLLACTION_H
#define _VERTICALSCROLLACTION_H

typedef unsigned int UINT;
class CScrollBar;
class VerticalScrollAction {
public:
	VerticalScrollAction();
	virtual ~VerticalScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) = 0;
};

#endif // !_VERTICALSCROLLACTION_H
