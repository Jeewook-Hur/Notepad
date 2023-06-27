//PageSettingCommand.h
/*
* 파일명칭:PageSettingCommand.h
* 기능:페이지 설정 커멘드의 헤더
* 작성자:허지욱
* 작성일자:2022/12/16
*/
#ifndef _PAGESETTINGCOMMAND_H
#define _PAGESETTINGCOMMAND_H
#include "Command.h"

class Notepannel;

class PageSettingCommand :public Command {
public:
	PageSettingCommand(Notepannel* notepannel);
	virtual ~PageSettingCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_PAGESETTINGCOMMAND_H
