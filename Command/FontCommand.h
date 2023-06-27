//FontCommand.h
/*
* 파일명칭:FontCommand.h
* 기능:폰트를 바꾸는 커멘드의 헤더
* 작성자:허지욱
* 작성일자:20220824
*/
#ifndef _FONTCOMMAND_H
#define _FONTCOMMAND_H
#include "Command.h"

class Notepannel;

class FontCommand :public Command {
public:
	FontCommand(Notepannel* notepannel);
	virtual ~FontCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_FONTCOMMAND_H
