//NotepadHelpCommand.h
/*
* 파일명칭:NotepadHelpCommand.h
* 기능:도움말 보기 메뉴 커멘드의 헤더
* 작성자:허지욱
* 작성일자:20230215
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