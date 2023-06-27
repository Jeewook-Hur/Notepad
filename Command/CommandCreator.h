//CommandCreator.h
/*
* ���ϸ�Ī:CommandCreator.h
* ���:Ŀ��� �Լ��� ����� ���
* �ۼ���:������
* �ۼ�����:20220826
*/
#ifndef _COMMNADCREATOR_H
#define _COMMNADCREATOR_H
#include "Notepannel.h"

typedef unsigned int UINT;
//class Notepannel;
class Glyph;
class Command;
class CommandCreator {
public:
	CommandCreator(Notepannel* notepannel);
	~CommandCreator();
	Command* Create(int id);
	Command* Create(int id, Glyph* paper);
	Command* Create(UINT nChar, UINT nRepCnt, UINT nFlags);
	Command* Create(WPARAM wParam, LPARAM lParam);
private:
	Notepannel* notepannel;
};

#endif // !_COMMNADCREATOR_H
