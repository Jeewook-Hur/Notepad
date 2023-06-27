//StatusBarCommand.h
/*
* ���ϸ�Ī:StatusBarCommand.h
* ���:����ǥ���� �޴��� ���
* �ۼ���:������
* �ۼ�����:2023/1/8
*/
#ifndef _STATUSBARCOMMAND_H
#define _STATUSBARCOMMAND_H
#include "Command.h"

class Notepannel;
class StatusBarCommand : public Command {
public:
	StatusBarCommand(Notepannel* notepannel);
	virtual ~StatusBarCommand();
	virtual void Execute();
	virtual void UnExecute();
private:
	Notepannel* notepannel;
};


#endif // !_STATUSBARCOMMAND_H