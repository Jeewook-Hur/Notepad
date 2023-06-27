//PrintCommand.h
/*
* ���ϸ�Ī:PrintCommand.h
* ���:�μ� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2022/12/19
*/
#ifndef _PRINTCOMMAND_H
#define _PRINTCOMMAND_H
#include "Command.h"

class Notepannel;

class PrintCommand :public Command {
public:
	PrintCommand(Notepannel* notepannel);
	virtual ~PrintCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_PRINTCOMMAND_H
