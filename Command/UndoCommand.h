//UndoCommand.h
/*
* 파일명칭:UndoCommand.h
* 기능:실행취소 커멘드의 헤더
* 작성자:허지욱
* 작성일자:2022/11/29
*/
#ifndef _UNDOCOMMAND_H
#define _UNDOCOMMAND_H
#include "Command.h"

class Notepannel;
class UndoCommand : public Command {
public:
	UndoCommand(Notepannel* notepannel);
	virtual ~UndoCommand();
	virtual void Execute();
	virtual void UnExecute();
private:
	Notepannel* notepannel;
};

#endif // !_UNDOCOMMAND_H
