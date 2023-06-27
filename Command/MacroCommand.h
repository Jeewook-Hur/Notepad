//MacroCommand.h
/*
* 파일명칭:MacroCommand.h
* 기능:커멘드를 스택형태로 저장하여 실행취소와 재실행을 실행한다.
* 작성자:허지욱
* 작성일자:2022/11/29
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

	int order; //현재 순서 
	int savePoint; //그냥 꺼도 되는 위치
private:
	Stack<Command*>* previous;
	Stack<Command*>* next;
	Stack<int>* previousFlag;
	Stack<int>* nextFlag;
};


#endif // !_MACROCOMMAND_H
