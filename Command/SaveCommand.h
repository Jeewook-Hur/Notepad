//SaveCommand.h
/*
* ���ϸ�Ī:SaveCommand.h
* ���:�����ϱ� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:20220826
*/
#ifndef _SAVECOMMAND_H
#define _SAVECOMMAND_H
#include"Command.h"

class Notepannel;
class SaveCommand : public Command {
public:
	SaveCommand(Notepannel* notepannel);
	virtual ~SaveCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_SAVECOMMAND_H