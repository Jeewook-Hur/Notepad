//FindCommand.h
/*
* 파일명칭:FindCommand.h
* 기능:찾기 커멘드의 헤더
* 작성자:허지욱
* 작성일자:2022/12/7
*/
#ifndef _FINDCOMMAND_H
#define _FINDCOMMAND_H
#include"Command.h"

class Notepannel;
class FindCommand : public Command {
public:
	FindCommand(Notepannel* notepannel);
	virtual ~FindCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_FINDCOMMAND_H