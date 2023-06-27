//AboutNotepadCommand.h
/*
* ���ϸ�Ī:AboutNotepadCommand.h
* ���:�޸��� ���� �޴� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:20230215
*/
#ifndef _ABOUTNOTEPADCOMMAND_H
#define _ABOUTNOTEPADCOMMAND_H
#include "Command.h"

class Notepannel;
class AboutNotepadCommand : public Command {
public:
	AboutNotepadCommand(Notepannel* notepannel);
	virtual ~AboutNotepadCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_ABOUTNOTEPADCOMMAND_H