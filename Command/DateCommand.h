//DateCommand.h
/*
* ���ϸ�Ī:DateCommand.h
* ���:��¥ Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2023/1/31
*/
#ifndef _DATECOMMAND_H
#define _DATECOMMAND_H
#include"Command.h"

class Notepannel;
class DateCommand : public Command {
public:
	DateCommand(Notepannel* notepannel);
	virtual ~DateCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_DATECOMMAND_H
