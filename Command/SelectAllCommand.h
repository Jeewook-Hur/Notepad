//SelectAllCommand.h
/*
* ���ϸ�Ī:SelectAllCommand.h
* ���:��ü�����ϴ� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _SELECTALLCOMMAND_H
#define _SELECTALLCOMMAND_H
#include "Command.h"

class Notepannel;
class SelectAllCommand : public Command {
public:
	SelectAllCommand(Notepannel* notepannel);
	virtual ~SelectAllCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_SELECTALLCOMMAND_H
