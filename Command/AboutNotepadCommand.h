//AboutNotepadCommand.h
/*
* 파일명칭:AboutNotepadCommand.h
* 기능:메모장 정보 메뉴 커멘드의 헤더
* 작성자:허지욱
* 작성일자:20230215
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