//PasteCommand.h
/*
* 파일명칭:PasteCommand.h
* 기능:붙여넣기를 하는 커멘드의 헤더
* 작성자:허지욱
* 작성일자:2022/11/21
*/
#ifndef _PASTECOMMAND_H
#define _PASTECOMMAND_H
#include "Command.h"

class Glyph;
class Notepannel;
class PasteCommand : public Command {
public:
	PasteCommand(Notepannel* notepannel);
	PasteCommand(Notepannel* notepannel, Glyph* paper);
	virtual ~PasteCommand();
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

#endif // !_PASTECOMMAND_H
