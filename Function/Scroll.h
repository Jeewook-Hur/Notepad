//Scroll.h
/*
* ���ϸ�Ī:Scroll.h
* ���:��ũ���� ������ �����ϴ� �Լ��� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#ifndef _SCROLL_H
#define _SCROLL_H

typedef unsigned int UINT;
class Notepannel;
class Scroll {
public:
	Scroll(Notepannel* notepannel);
	~Scroll();
	void Move(int x, int lineOrder);
	//void MoveToClientLocation();
	UINT pageSizeX;
	UINT pageSizeY;
	int maxX;
	int maxY;
private:
	Notepannel* notepannel;
};

#endif // !_SCROLL_H
