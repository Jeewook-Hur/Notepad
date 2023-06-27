//ZoomOutCommand.h
/*
* ���ϸ�Ī:ZoomOutCommand.h
* ���:ȭ�� ����ϱ� �޴��� ���� ���(Command)�� ���
* �ۼ���:������
* �ۼ�����:20221007
*/
#ifndef _ZOOMOUTCOMMAND_H
#define _ZOOMOUTCOMMAND_H
#include "Command.h"

class Notepannel;
class ZoomOutCommand : public Command {
public:
	ZoomOutCommand(Notepannel* notepannel);
	virtual ~ZoomOutCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_ZOOMOUTCOMMAND_H
