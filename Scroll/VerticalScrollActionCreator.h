//VerticalScrollActionCreator.h
/*
* ���ϸ�Ī:VerticalScrollActionCreator.h
* ���:���ν�ũ�� �׼��� �Լ��� ����� ���
* �ۼ���:������
* �ۼ�����:20220928
*/
#ifndef _VERTICALSCROLLACTIONCREATOR_H
#define _VERTICALSCROLLACTIONCREATOR_H

typedef unsigned int UINT;
class CScrollBar;
class Notepannel;
class VerticalScrollAction;
class VerticalScrollActionCreator {
public:
	VerticalScrollActionCreator(Notepannel* notepannel);
	~VerticalScrollActionCreator();
	VerticalScrollAction* Create(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALSCROLLACTIONCREATOR_H
