//SaveAsCommand.h
/*
* 파일명칭:SaveAsCommand.h
* 기능:다른이름으로 저장하기 커멘드의 헤더
* 작성자:허지욱
* 작성일자:20220826
*/
#ifndef _SAVEASCOMMAND_H
#define _SAVEASCOMMAND_H
#include"Command.h"

class Notepannel;
class SaveAsCommand : public Command {
public:
	SaveAsCommand(Notepannel* notepannel);
	virtual ~SaveAsCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_SAVEASCOMMAND_H