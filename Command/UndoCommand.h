//UndoCommand.h
/*
* ���ϸ�Ī:UndoCommand.h
* ���:������� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2022/11/29
*/
#ifndef _UNDOCOMMAND_H
#define _UNDOCOMMAND_H
#include "Command.h"

class Notepannel;
class UndoCommand : public Command {
public:
	UndoCommand(Notepannel* notepannel);
	virtual ~UndoCommand();
	virtual void Execute();
	virtual void UnExecute();
private:
	Notepannel* notepannel;
};

#endif // !_UNDOCOMMAND_H
