//LineWrapCommand.h
/*
* 파일명칭:LineWrapCommand.h
* 기능:자동 줄 바꿈 메뉴의 헤더
* 작성자:허지욱
* 작성일자:20220920
*/
#ifndef _LINEWRAPCOMMAND_H
#define _LINEWRAPCOMMAND_H
#include "Command.h"

class Notepannel;
class LineWrapCommand : public Command {
public:
	LineWrapCommand(Notepannel* notepannel);
	virtual ~LineWrapCommand();
	virtual void Execute();
	virtual void UnExecute();
private:
	Notepannel* notepannel;
};


#endif // !_LINEWRAPCOMMAND_H