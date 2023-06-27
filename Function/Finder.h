//Finder.h
/*
* ���ϸ�Ī:Finder.h
* ���:ã��� �ٲٱ� ������ ����Ѵ�. 
* �ۼ���:������
* �ۼ�����:2022/12/7
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
	BOOL findNext; //ã��â���� ���� ã�⸦ Ŭ���ߴ��� Ȯ���Ѵ�.
	BOOL isTerminating; //ã��â���� �ݱ⸦ Ŭ���ߴ��� Ȯ���Ѵ�.
	BOOL searchDown; //ã�� ������ �д´�.
	BOOL matchWholeWord; //�ܾ������ ã�Ⱑ üũ�Ǿ����� Ȯ���Ѵ�. 
	BOOL matchCase; //��ҹ��� ���� ���ΰ� üũ�Ǿ����� Ȯ���Ѵ�.
private:
	Notepannel* notepannel;
};

#endif // !_FINDER_H
