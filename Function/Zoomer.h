//Zoomer.h
/*
* ���ϸ�Ī:Zoomer.h
* ���:Ŭ���̾�Ʈ�� ������ �����ϰ� �����ϴ� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/10/7
*/
#ifndef _ZOOMER_H
#define _ZOOMER_H

class Zoomer {
public:
	Zoomer();
	Zoomer(int magnification);
	~Zoomer();
	int Change(int magnification);
	int magnification; // 10~500�� ������ ���´�.
};

#endif // !_ZOOMER_H
