//NotepadHelpCommand.h
/*
* ���ϸ�Ī:NotepadHelpCommand.h
* ���:���� ���� �޴� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:20230215
*/
#ifndef _NOTEPADHELPCOMMAND_H
#define _NOTEPADHELPCOMMAND_H
#include "Command.h"

class Notepannel;
class NotepadHelpCommand : public Command {
public:
	NotepadHelpCommand(Notepannel* notepannel);
	virtual ~NotepadHelpCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_NOTEPADHELPCOMMAND_H