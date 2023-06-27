//Command.h
/*
* 파일명칭:Command.h
* 기능:커멘트 가상함수의 헤더
* 작성자:허지욱
* 작성일자:20220824
*/
#ifndef _COMMAND_H
#define _COMMAND_H

typedef signed long int Long;
class Command {
public:
	Command();
	virtual ~Command() = 0;
	virtual void Execute();
	virtual void UnExecute();
};

#endif// !_COMMAND_H