//NewCommand.h
/*
* ���ϸ�Ī:NewCommand.h
* ���:���� ����� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:20221012
*/
#ifndef _NEWCOMMAND_H
#define _NEWCOMMAND_H
#include"Command.h"

class Notepannel;
class NewCommand : public Command {
public:
	NewCommand(Notepannel* notepannel);
	virtual ~NewCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_NEWCOMMAND_H