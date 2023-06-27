//BackspaceCommand.h
/*
* 파일명칭:BackspaceCommand.h
* 기능:백스페이스 커멘드의 헤더
* 작성자:허지욱
* 작성일자:2022/12/2
*/
#ifndef _BACKSPACECOMMAND_H
#define _BACKSPACECOMMAND_H
#include "Command.h"
#include "Notepannel.h"

class Notepannel;
class Glyph;
class BackspaceCommand : public Command {
public:
	BackspaceCommand(Notepannel* notepannel, UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual ~BackspaceCommand();
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

#endif // !_BACKSPACECOMMAND_H