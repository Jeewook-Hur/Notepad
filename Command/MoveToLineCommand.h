//MoveToLineCommand.h
/*
* ���ϸ�Ī:MoveToLineCommand.h
* ���:�� �̵� �޴��� ���
* �ۼ���:������
* �ۼ�����:2023/2/6
*/
#ifndef _MOVETOLINECOMMAND_H
#define _MOVETOLINECOMMAND_H
#include "Command.h"

class Notepannel;

class MoveToLineCommand :public Command {
public:
	MoveToLineCommand(Notepannel* notepannel);
	virtual ~MoveToLineCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_MOVETOLINECOMMAND_H
