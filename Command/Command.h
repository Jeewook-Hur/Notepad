//Command.h
/*
* ���ϸ�Ī:Command.h
* ���:Ŀ��Ʈ �����Լ��� ���
* �ۼ���:������
* �ۼ�����:20220824
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