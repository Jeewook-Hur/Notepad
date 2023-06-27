//ClientLocation.h
/*
* ���ϸ�Ī:ClientLocation.h
* ���:Ŭ���̾�Ʈ�� ������ ���� ��ǥ�� ��Ÿ���� ������ ���
* �ۼ���:������
* �ۼ�����:20220923
*/
#ifndef _CLIENTLOCATION_H
#define _CLIENTLOCATION_H

typedef int BOOL;
class Notepannel;
class Glyph;
class ClientLocation {
public:
	ClientLocation(Notepannel* notepannel);
	~ClientLocation();
	void Move(int x, int lineOrder);
	//void MoveToCurrent();

	//void MoveBackInPercentage(int percentageX, int percentageY);
	
	//void CheckCaretXIsInside(BOOL* isIn, int* distance);
	//void CheckCaretYIsInside(BOOL* isIn, int* distance);

	//int GetCaretXPercentageInsideClient();
	//int GetCaretYPercentageInsideClient();

	int x;
	int lineOrder;
	//BOOL lastPage;
private:
	Notepannel* notepannel;
};

#endif // !_CLIENTLOCATION_H
