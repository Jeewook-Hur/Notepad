//MoveToLineCommand.h
/*
* 파일명칭:MoveToLineCommand.h
* 기능:줄 이동 메뉴의 헤더
* 작성자:허지욱
* 작성일자:2023/2/6
*/
#ifndef _MOVETOLINECOMMAND_H
#define _MOVETOLINECOMMAND_H
#include "Command.h"

class Notepannel;

class MoveToLineCommand :public Command {
public:
	MoveToLineCommand(Notepannel* notepannel);
	virtual ~MoveToLineCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_MOVETOLINECOMMAND_H
