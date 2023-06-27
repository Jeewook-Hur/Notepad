//LineWrapCommand.h
/*
* ���ϸ�Ī:LineWrapCommand.h
* ���:�ڵ� �� �ٲ� �޴��� ���
* �ۼ���:������
* �ۼ�����:20220920
*/
#ifndef _LINEWRAPCOMMAND_H
#define _LINEWRAPCOMMAND_H
#include "Command.h"

class Notepannel;
class LineWrapCommand : public Command {
public:
	LineWrapCommand(Notepannel* notepannel);
	virtual ~LineWrapCommand();
	virtual void Execute();
	virtual void UnExecute();
private:
	Notepannel* notepannel;
};


#endif // !_LINEWRAPCOMMAND_H