//FindCommand.h
/*
* ���ϸ�Ī:FindCommand.h
* ���:ã�� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2022/12/7
*/
#ifndef _FINDCOMMAND_H
#define _FINDCOMMAND_H
#include"Command.h"

class Notepannel;
class FindCommand : public Command {
public:
	FindCommand(Notepannel* notepannel);
	virtual ~FindCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_FINDCOMMAND_H