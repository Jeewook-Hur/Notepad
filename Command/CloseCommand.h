//CloseCommand.h
/*
* 파일명칭:CloseCommand.h
* 기능:닫기 커멘드의 헤더
* 작성자:허지욱
* 작성일자:20220826
*/
#ifndef _CLOSECOMMAND_H
#define _CLOSECOMMAND_H
#include "Command.h"

class Notepannel;
class CloseCommand : public Command {
public:
	CloseCommand(Notepannel* notepannel);
	virtual ~CloseCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_CLOSECOMMAND_H