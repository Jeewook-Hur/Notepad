//Clipboard.h
/*
* ���ϸ�Ī:Clipboard.h
* ���:Ŭ�������� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _CLIPBOARD_H
#define _CLIPBOARD_H
#include<string>
using namespace std;

typedef int BOOL;
class Notepannel;
class Clipboard {
public:
	Clipboard(Notepannel* notepannel);
	~Clipboard();
	BOOL Copy(string stringToCopy);
	string GetData();
	BOOL Check();
private:
	Notepannel* notepannel;
};

#endif // !_CLIPBOARD_H
