//LoadCommand.h
/*
* ���ϸ�Ī:LoadCommand.h
* ���:�����ϱ� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:20220826
*/
#ifndef _LOADCOMMAND_H
#define _LOADCOMMAND_H
#include"Command.h"

class Notepannel;
class LoadCommand : public Command {
public:
	LoadCommand(Notepannel* notepannel);
	virtual ~LoadCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_LOADCOMMAND_H