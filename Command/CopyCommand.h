//CopyCommand.h
/*
* ���ϸ�Ī:CopyCommand.h
* ���:���縦 �ϴ� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _COPYCOMMAND_H
#define _COPYCOMMAND_H
#include "Command.h"

class Notepannel;
class CopyCommand : public Command {
public:
	CopyCommand(Notepannel* notepannel);
	virtual ~CopyCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_COPYCOMMAND_H
