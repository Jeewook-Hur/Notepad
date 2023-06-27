//SelectAllCommand.h
/*
* 파일명칭:SelectAllCommand.h
* 기능:전체선택하는 커멘드의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#ifndef _SELECTALLCOMMAND_H
#define _SELECTALLCOMMAND_H
#include "Command.h"

class Notepannel;
class SelectAllCommand : public Command {
public:
	SelectAllCommand(Notepannel* notepannel);
	virtual ~SelectAllCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_SELECTALLCOMMAND_H
