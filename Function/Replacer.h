//Replacer.h
/*
* 파일명칭:Replacer.h
* 기능:찾기와 바꾸기 내용을 기억한다.
* 작성자:허지욱
* 작성일자:2022/12/7
*/
#ifndef _REPLACER_H
#define _REPLACER_H
#include<string>
#include "Notepannel.h"
using namespace std;

class Notepannel;
class Replacer {
public:
	Replacer(Notepannel* notepannel, string find = "", string replace = "");
	Replacer(Notepannel* notepannel, WPARAM wParam, LPARAM lParam);
	~Replacer();
	void ReplaceCurrent();

	string replace;
	Glyph* paperToReplace;
	BOOL replaceAll;
	BOOL replaceCurrent;
private:
	Notepannel* notepannel;
};

#endif // !_REPLACER_H
