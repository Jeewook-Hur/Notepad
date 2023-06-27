//HorizontalScrollActionCreator.h
/*
* ���ϸ�Ī:HorizontalScrollActionCreator.h
* ���:���ν�ũ�� �׼��� �Լ��� ����� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#ifndef _HORIZONTALSCROLLACTIONCREATOR_H
#define _HORIZONTALSCROLLACTIONCREATOR_H

typedef unsigned int UINT;
class CScrollBar;
class Notepannel;
class HorizontalScrollAction;
class HorizontalScrollActionCreator {
public:
	HorizontalScrollActionCreator(Notepannel* notepannel);
	~HorizontalScrollActionCreator();
	HorizontalScrollAction* Create(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALSCROLLACTIONCREATOR_H
