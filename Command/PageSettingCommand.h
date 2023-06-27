//PageSettingCommand.h
/*
* ���ϸ�Ī:PageSettingCommand.h
* ���:������ ���� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2022/12/16
*/
#ifndef _PAGESETTINGCOMMAND_H
#define _PAGESETTINGCOMMAND_H
#include "Command.h"

class Notepannel;

class PageSettingCommand :public Command {
public:
	PageSettingCommand(Notepannel* notepannel);
	virtual ~PageSettingCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_PAGESETTINGCOMMAND_H
