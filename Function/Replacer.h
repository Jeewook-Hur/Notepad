//Replacer.h
/*
* ���ϸ�Ī:Replacer.h
* ���:ã��� �ٲٱ� ������ ����Ѵ�.
* �ۼ���:������
* �ۼ�����:2022/12/7
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
