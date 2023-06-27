//DeleteCommand.h
/*
* 파일명칭:DeleteCommand.h
* 기능:삭제 커멘드의 헤더
* 작성자:허지욱
* 작성일자:2022/11/21
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