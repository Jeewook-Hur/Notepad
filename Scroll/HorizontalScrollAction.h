//HorizontalScrollAction.h
/*
* ���ϸ�Ī:HorizontalScrollAction.h
* ���:���ν�ũ�� �׼��� �����Լ� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#ifndef _HORIZONTALSCROLLACTION_H
#define _HORIZONTALSCROLLACTION_H

typedef unsigned int UINT;
class CScrollBar;
class HorizontalScrollAction {
public:
	HorizontalScrollAction();
	virtual ~HorizontalScrollAction();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) = 0;
};

#endif // !_HORIZONTALSCROLLACTION_H
