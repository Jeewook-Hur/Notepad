//PrintCommand.h
/*
* 파일명칭:PrintCommand.h
* 기능:인쇄 커멘드의 헤더
* 작성자:허지욱
* 작성일자:2022/12/19
*/
#ifndef _PRINTCOMMAND_H
#define _PRINTCOMMAND_H
#include "Command.h"

class Notepannel;

class PrintCommand :public Command {
public:
	PrintCommand(Notepannel* notepannel);
	virtual ~PrintCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_PRINTCOMMAND_H
