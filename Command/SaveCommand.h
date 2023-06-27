//SaveCommand.h
/*
* 파일명칭:SaveCommand.h
* 기능:저장하기 커멘드의 헤더
* 작성자:허지욱
* 작성일자:20220826
*/
#ifndef _SAVECOMMAND_H
#define _SAVECOMMAND_H
#include"Command.h"

class Notepannel;
class SaveCommand : public Command {
public:
	SaveCommand(Notepannel* notepannel);
	virtual ~SaveCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_SAVECOMMAND_H