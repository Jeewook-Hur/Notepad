//ReplaceCommand.h
/*
* ���ϸ�Ī:ReplaceCommand.h
* ���:�ٲٱ� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2022/12/8
*/
#ifndef _REPLACECOMMAND_H
#define _REPLACECOMMAND_H
#include"Command.h"

class Notepannel;
class ReplaceCommand : public Command {
public:
	ReplaceCommand(Notepannel* notepannel);
	virtual ~ReplaceCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_REPLACECOMMAND_H