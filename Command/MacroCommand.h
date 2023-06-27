//MacroCommand.h
/*
* ���ϸ�Ī:MacroCommand.h
* ���:Ŀ��带 �������·� �����Ͽ� ������ҿ� ������� �����Ѵ�.
* �ۼ���:������
* �ۼ�����:2022/11/29
*/
#ifndef _MACROCOMMAND_H
#define _MACROCOMMAND_H
#include "Command.h"
#include "Stack.h"

class MacroCommand {
public:
	MacroCommand();
	~MacroCommand();
	void Add(Command* command, int flag = 0);
	int Undo();
	int Redo();
	bool ToUndo();
	bool ToRedo();
	void FlagUp();
	void FlagDown();
	int ChangeSavePoint();

	int order; //���� ���� 
	int savePoint; //�׳� ���� �Ǵ� ��ġ
private:
	Stack<Command*>* previous;
	Stack<Command*>* next;
	Stack<int>* previousFlag;
	Stack<int>* nextFlag;
};


#endif // !_MACROCOMMAND_H
