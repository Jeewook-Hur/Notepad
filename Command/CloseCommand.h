//CloseCommand.h
/*
* ���ϸ�Ī:CloseCommand.h
* ���:�ݱ� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:20220826
*/
#ifndef _CLOSECOMMAND_H
#define _CLOSECOMMAND_H
#include "Command.h"

class Notepannel;
class CloseCommand : public Command {
public:
	CloseCommand(Notepannel* notepannel);
	virtual ~CloseCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_CLOSECOMMAND_H