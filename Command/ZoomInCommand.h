//ZoomInCommand.h
/*
* ���ϸ�Ī:ZoomInCommand.h
* ���:ȭ�� Ȯ���ϱ� �޴��� ���� ���(Command)�� ���
* �ۼ���:������
* �ۼ�����:20221007
*/
#ifndef _ZOOMINCOMMAND_H
#define _ZOOMINCOMMAND_H
#include "Command.h"

class Notepannel;
class ZoomInCommand : public Command {
public:
	ZoomInCommand(Notepannel* notepannel);
	virtual ~ZoomInCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_ZOOMINCOMMAND_H
