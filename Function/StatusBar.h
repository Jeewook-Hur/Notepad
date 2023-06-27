//StatusBar.h
/*
* 파일명칭:StatusBar.h
* 기능:상태표시줄 클래스의 헤더
* 작성자:허지욱
* 작성일자:2023/1/8
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
