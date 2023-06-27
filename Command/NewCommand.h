//NewCommand.h
/*
* 파일명칭:NewCommand.h
* 기능:새로 만들기 커멘드의 헤더
* 작성자:허지욱
* 작성일자:20221012
*/
#ifndef _NEWCOMMAND_H
#define _NEWCOMMAND_H
#include"Command.h"

class Notepannel;
class NewCommand : public Command {
public:
	NewCommand(Notepannel* notepannel);
	virtual ~NewCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_NEWCOMMAND_H