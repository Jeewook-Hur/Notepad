//SaveAsCommand.h
/*
* ���ϸ�Ī:SaveAsCommand.h
* ���:�ٸ��̸����� �����ϱ� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:20220826
*/
#ifndef _SAVEASCOMMAND_H
#define _SAVEASCOMMAND_H
#include"Command.h"

class Notepannel;
class SaveAsCommand : public Command {
public:
	SaveAsCommand(Notepannel* notepannel);
	virtual ~SaveAsCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_SAVEASCOMMAND_H