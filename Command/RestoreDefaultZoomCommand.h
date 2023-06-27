//RestoreDefaultZoomCommand.h
/*
* ���ϸ�Ī:RestoreDefaultZoomCommand.h
* ���:ȭ�� Ȯ��/����ϱ� �⺻�� ���� �޴��� ���� ���(Command)�� ���
* �ۼ���:������
* �ۼ�����:20221007
*/
#ifndef _RESTOREDEFALTZOOM_H
#define _RESTOREDEFALTZOOM_H
#include "Command.h"

class Notepannel;
class RestoreDefaultZoomCommand : public Command {
public:
	RestoreDefaultZoomCommand(Notepannel* notepannel);
	virtual ~RestoreDefaultZoomCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_RESTOREDEFALTZOOM_H
