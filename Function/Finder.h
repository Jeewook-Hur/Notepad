//Finder.h
/*
* 파일명칭:Finder.h
* 기능:찾기와 바꾸기 내용을 기억한다. 
* 작성자:허지욱
* 작성일자:2022/12/7
*/
#ifndef _FINDER_H
#define _FINDER_H
#include<string>
#include "Notepannel.h"
using namespace std;

class Notepannel;
class Finder {
public:
	Finder(Notepannel* notepannel, string find = "", string replace = "");
	Finder(Notepannel* notepannel, WPARAM wParam, LPARAM lParam);
	~Finder();
	Long Find();
	Long SearchNear(Long lineOrder, Long charIndex);
	void SelectResult(Long index);

	string find;
	BOOL findNext; //찾기창에서 다음 찾기를 클릭했는지 확인한다.
	BOOL isTerminating; //찾기창에서 닫기를 클릭했는지 확인한다.
	BOOL searchDown; //찾는 방향을 읽는다.
	BOOL matchWholeWord; //단어단위로 찾기가 체크되었는지 확인한다. 
	BOOL matchCase; //대소문자 구분 여부가 체크되었는지 확인한다.
private:
	Notepannel* notepannel;
};

#endif // !_FINDER_H
