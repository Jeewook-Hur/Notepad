//ReplaceCommand.h
/*
* 파일명칭:ReplaceCommand.h
* 기능:바꾸기 커멘드의 헤더
* 작성자:허지욱
* 작성일자:2022/12/8
*/
#ifndef _REPLACECOMMAND_H
#define _REPLACECOMMAND_H
#include"Command.h"

class Notepannel;
class ReplaceCommand : public Command {
public:
	ReplaceCommand(Notepannel* notepannel);
	virtual ~ReplaceCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_REPLACECOMMAND_H