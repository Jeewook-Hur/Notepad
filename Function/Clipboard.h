//Clipboard.h
/*
* 파일명칭:Clipboard.h
* 기능:클립보드의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
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
