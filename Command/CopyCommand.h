//CopyCommand.h
/*
* 파일명칭:CopyCommand.h
* 기능:복사를 하는 커멘드의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#ifndef _COPYCOMMAND_H
#define _COPYCOMMAND_H
#include "Command.h"

class Notepannel;
class CopyCommand : public Command {
public:
	CopyCommand(Notepannel* notepannel);
	virtual ~CopyCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_COPYCOMMAND_H
