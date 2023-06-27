//FontCommand.h
/*
* ���ϸ�Ī:FontCommand.h
* ���:��Ʈ�� �ٲٴ� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:20220824
*/
#ifndef _FONTCOMMAND_H
#define _FONTCOMMAND_H
#include "Command.h"

class Notepannel;

class FontCommand :public Command {
public:
	FontCommand(Notepannel* notepannel);
	virtual ~FontCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_FONTCOMMAND_H
