//Caret.h
/*
* ���ϸ�Ī:Caret.h
* ���:ĳ���� ������ �����ϴ� ��� � �۲��̾ ĳ���� ����ϰ� �Ѵ�.
* �ۼ���:������
* �ۼ�����:2022/7/20
*/
#ifndef _CARET_H
#define _CARET_H
//#include<afxwin.h>

//������ǥ - ������ �������� �� ��ǥ - ��ǻ� ���̿� �����Ǿ��ִ�. 
//Ŭ���̾�Ʈ��ǥ - �ȼ��� �������� �� ��ǥ - �۲ÿ� ���� �����ȴ�.

class Notepannel;
class Glyph;
class Caret {
public:
	Caret(Notepannel* notepannel);
	~Caret();
	void Create(int width, int height);
	void Move(int x, int y);
	void ShowCaret();
	void HideCaret();

	//������ǥ
	//ĳ���� ������ �������� �� ��ǥ
	int x; //-1�� ����
	int y; //���� �׻� �����Ƿ� 0�� ����
	int corX;
	int corY;
private:
	Notepannel* notepannel;

};
#endif // !_CARET_H