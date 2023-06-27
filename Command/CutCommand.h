//CutCommand.h
/*
* ���ϸ�Ī:CutCommand.h
* ���:�߶󳻱⸦ �ϴ� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#ifndef _CUTCOMMAND_H
#define _CUTCOMMAND_H
#include "Command.h"

class Notepannel;
class Glyph;
class CutCommand : public Command {
public:
	CutCommand(Notepannel* notepannel);
	virtual ~CutCommand();
	virtual void Execute();
	virtual void UnExecute();
private:
	Notepannel* notepannel;
	Glyph* previousPaper;
	Long frontLineLocation;
	Long frontCharLocation;
	Long endLineLocation;
	Long endCharLocation;
};

#endif // !_CUTCOMMAND_H
