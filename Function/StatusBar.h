//StatusBar.h
/*
* ���ϸ�Ī:StatusBar.h
* ���:����ǥ���� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2023/1/8
*/
#ifndef _STATUSBAR_H
#define _STATUSBAR_H
#include<string>
using namespace std;

class Notepad;
class StatusBar {
public:
	StatusBar(Notepad* notepad);
	~StatusBar();
	void UpdateStatusBar();
	void ShowStatusBar();
	void HideStatusBar();

	string currentLineAndColumn;
	string currentZoom;
	string bytecode;
	string incoding;
	int heigth;
private:
	Notepad* notepad;
};

#endif // !_STATUSBAR_H
