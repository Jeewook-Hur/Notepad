//DeleteCommand.h
/*
* ���ϸ�Ī:DeleteCommand.h
* ���:���� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2022/11/21
*/
#ifndef _DELETECOMMAND_H
#define _DELETECOMMAND_H
#include "Command.h"
#include "Notepannel.h"

class Notepannel;
class Glyph;
class DeleteCommand : public Command {
public:
	DeleteCommand(Notepannel* notepannel);
	virtual ~DeleteCommand();
	virtual void Execute();
	virtual void UnExecute();
private:
	Notepannel* notepannel;
	Glyph* previousPaper;
	Long frontLineLocation;
	Long frontCharLocation;
	Long endLineLocation;
	Long endCharLocation;
	BOOL wasSelected = FALSE;
};

#endif // !_DELETECOMMAND_H