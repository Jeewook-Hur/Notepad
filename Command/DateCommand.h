//DateCommand.h
/*
* 파일명칭:DateCommand.h
* 기능:날짜 커멘드의 헤더
* 작성자:허지욱
* 작성일자:2023/1/31
*/
#ifndef _DATECOMMAND_H
#define _DATECOMMAND_H
#include"Command.h"

class Notepannel;
class DateCommand : public Command {
public:
	DateCommand(Notepannel* notepannel);
	virtual ~DateCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};


#endif // !_DATECOMMAND_H
