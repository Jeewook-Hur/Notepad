//LoadCommand.h
/*
* 파일명칭:LoadCommand.h
* 기능:적재하기 커멘드의 헤더
* 작성자:허지욱
* 작성일자:20220826
*/
#ifndef _LOADCOMMAND_H
#define _LOADCOMMAND_H
#include"Command.h"

class Notepannel;
class LoadCommand : public Command {
public:
	LoadCommand(Notepannel* notepannel);
	virtual ~LoadCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_LOADCOMMAND_H