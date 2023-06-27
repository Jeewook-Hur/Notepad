//DocumentVirtualSize.h
/*
* ���ϸ�Ī:DocumentVirtualSize.h
* ���:Ŭ���̾�Ʈ�� ���� ũ��� ���� ������ ���� ũ�⸦ ���ϴ� ���
* �ۼ���:������
* �ۼ�����:20220923
*/
#ifndef _DOCUMENTVIRTUALSIZE_H
#define _DOCUMENTVIRTUALSIZE_H

class Glyph;
class Notepannel;
class DocumentVirtualSize {
public:
	DocumentVirtualSize(Notepannel* notepannel);
	~DocumentVirtualSize();
	int MaxX;
	int MaxY;
	int availableX;
	int availableLine; //�̵� ������ �� ��(����)
private:
	Notepannel* notepannel;
};

#endif // !_DOCUMENTVIRTUALSIZE_H
