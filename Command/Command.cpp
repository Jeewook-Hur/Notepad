//Command.cpp
/*
* 파일명칭:Command.cpp
* 기능:커멘드 가상함수
*/
#include "Command.h"

/*
* 함수명칭:Command
* 기능:생성자
*/
Command::Command() {
}

/*
* 함수명칭:~Command
* 기능:소멸자
*/
Command::~Command() {
}

/*
* 함수명칭:Execute
* 기능:가상함수 실행
*/
void Command::Execute() {
}

/*
* 함수명칭:UnExecute
* 기능:가상함수 실행취소
*/
void Command::UnExecute() {
}