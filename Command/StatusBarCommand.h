//StatusBarCommand.h
/*
* 파일명칭:StatusBarCommand.h
* 기능:상태표시줄 메뉴의 헤더
* 작성자:허지욱
* 작성일자:2023/1/8
*/
#ifndef _STATUSBARCOMMAND_H
#define _STATUSBARCOMMAND_H
#include "Command.h"

class Notepannel;
class StatusBarCommand : public Command {
public:
	StatusBarCommand(Notepannel* notepannel);
	virtual ~StatusBarCommand();
	virtual void Execute();
	virtual void UnExecute();
private:
	Notepannel* notepannel;
};


#endif // !_STATUSBARCOMMAND_H