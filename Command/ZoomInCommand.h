//ZoomInCommand.h
/*
* 파일명칭:ZoomInCommand.h
* 기능:화면 확대하기 메뉴에 대한 명령(Command)의 헤더
* 작성자:허지욱
* 작성일자:20221007
*/
#ifndef _ZOOMINCOMMAND_H
#define _ZOOMINCOMMAND_H
#include "Command.h"

class Notepannel;
class ZoomInCommand : public Command {
public:
	ZoomInCommand(Notepannel* notepannel);
	virtual ~ZoomInCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_ZOOMINCOMMAND_H
