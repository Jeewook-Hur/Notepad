//DateCommand.cpp
/*
* 파일명칭:DateCommand.cpp
* 기능:날짜 커멘드
* 작성자:허지욱
* 작성일자:2023/1/31
*/
#include "DateCommand.h"
#include "Notepannel.h"
#include "Paper.h"
#include "GlyphCreater.h"
#include "CommandCreator.h"
#include "MacroCommand.h"
#include "resource.h"
#include<ctime>
#include<string>
#pragma warning(disable:4996) //localtime에서 필요 

/*
* 함수명칭:DateCommand
* 기능:생성자
*/
DateCommand::DateCommand(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* 함수명칭:~DateCommand
* 기능:소멸자
*/
DateCommand::~DateCommand() {
}

/*
* 함수명칭:Execute
* 기능:커멘드를 실행한다. 
*/
void DateCommand::Execute() {
	time_t timer; 
	struct tm* today;
	time(&timer);
	today = localtime(&timer);
	int year = today->tm_year + 1900;
	int month = today->tm_mon + 1;
	int day = today->tm_mday;
	int hour = today->tm_hour;
	int min = today->tm_min;
	CString noon = "오전";

	if (hour > 12) {
		noon = "오후";
		hour = hour - 12;
	}
	
	CString timeToPrint;
	timeToPrint.Format("%s %d:%02d %d-%d-%d", _T(noon), hour, min, year, month, day);

	string timeInString;
	timeInString = timeToPrint;

	GlyphCreater glyphCreater;
	Glyph* datePaper;
	datePaper = glyphCreater.Create(timeInString);

	CommandCreator commandCreater(this->notepannel);
	Command* command = NULL;

	if (this->notepannel->isSelected == TRUE) {//선택되었으면
		//선택된 내용을 삭제한다. 
		command = commandCreater.Create(IDM_FORMAT_DELETE);
		if (command != NULL) {
			command->Execute();
			this->notepannel->macroCommand->Add(command, 0);
			command = NULL;
		}
	}
	//현재 위치에 바꿀 내용을 붙인다. 
	command = commandCreater.Create(IDM_FORMAT_PASTE, datePaper);
	if (command != NULL) {
		command->Execute();
		this->notepannel->macroCommand->Add(command, 1); //매크로 플래그를 올린다. 
	}




	//업데이트를 한다.(위치)
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->documentUploaded = TRUE;
	this->notepannel->Notify();
	//클라이언트를 갱신한다.
	this->notepannel->Invalidate(TRUE);

	this->notepannel->ShowCaret();


	delete datePaper;
}
