//Select.h
/*
* ���ϸ�Ī:Select.h
* ���:�����ϱ⿡ ���� ����� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20221014
*/
#ifndef _SELECT_H 
#define _SELECT_H
#define FALSE 0
#define TRUE 1

typedef int BOOL;
class Notepannel;
class Glyph;
class Select {
public:
	Select(Notepannel* notepannel, int previousXIndex = -1, int previousLineOrder = 0, int currentXIndex = -1, int currentLineOrder = 0);
	~Select();
	void MoveCurrent(int currentXIndex, int currentLineOrder);
	BOOL IsSelected(int lineOrder, int charOrder);
	BOOL IsEqual(Glyph* other);
	int previousXIndex;
	int previousLineOrder;
	int currentXIndex; 
	int currentLineOrder;
	//�ڵ����� �ϴ� �κ�
	int frontXIndex;
	int frontLineOrder;
	int endXIndex;
	int endLineOrder;
private:
	Notepannel* notepannel;
};

#endif // !_SELECT_H
