//ClientMatrix.h
/*
* ���ϸ�Ī:ClientMatrix.h
* ���:Ŭ���̾�Ʈ�� ���� ���������� ����Ͽ� �����ϴ� ������ ���
* �ۼ���:������
* �ۼ�����:20220928
*/
#ifndef _CLIENTMATRIX_H
#define _CLIENTMATRIX_H

class Notepannel;
class ClientMatrix {
public:
	ClientMatrix(Notepannel* notepannel);
	~ClientMatrix();

	int width;
	int height;
	int lineNumberInPage;
	int widthOneThird;

private:
	Notepannel* notepannel;
};

#endif // !_CLIENTMATRIX_H
