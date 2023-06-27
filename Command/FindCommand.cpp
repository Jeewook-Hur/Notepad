//FindCommand.cpp
/*
* 파일명칭:FindCommand.cpp
* 기능:닫기 커멘드
* 작성자:허지욱
* 작성일자:20220826
*/
#include "FindCommand.h"
#include "Notepannel.h"
#include "Finder.h"
#include "ResultFound.h"
#include "Select.h"
#include "Paper.h"
#include <afxdlgs.h>
#include<string>
using namespace std;

/*
* 함수명칭:FindCommand
* 기능:생성자
*/
FindCommand::FindCommand(Notepannel* notepannel) : notepannel(notepannel) {
}

/*
* 함수명칭:~FindCommand
* 기능:소멸자
*/
FindCommand::~FindCommand() {
}

/*
* 함수명칭:Execute
* 기능:닫기 커멘드를 실행하다
*/
void FindCommand::Execute() {
	CFindReplaceDialog* cFindDialog = NULL;
	Glyph* clone;
	string stringWritten = this->notepannel->resultFound->stringToFind;
	string stringSelected = "";
	//string test = "테스트 문구"; //나중에 찾기클래스의 내용으로 대체 
	Long frontLineOrder = this->notepannel->select->frontLineOrder;
	Long frontCharIndex = this->notepannel->select->frontXIndex;
	Long endLineOrder = this->notepannel->select->endLineOrder;
	Long endCharIndex = this->notepannel->select->endXIndex;

	//찾기 공통대화상자를 띄운다. 
	cFindDialog = new CFindReplaceDialog;
	
	if (this->notepannel->isSelected == FALSE) { //종이에서 선택되어있지 않으면
		//저장된 찾기 내용을 찾기 대화상자의 찾는내용에 적는다. 
		//cFindDialog->Create(TRUE, test.c_str(), NULL, FR_DOWN, this->notepannel);
		cFindDialog->Create(TRUE, stringWritten.c_str(), NULL, FR_DOWN, this->notepannel);
	}
	else { //종이에서 선택되어 있으면
		//선택된 내용을 찾기대화상자의 찾는내용에 적는다. 
		clone = this->notepannel->paper->Clone(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);
		clone->MergeAllDummyLines();
		stringSelected = clone->GetString();
		delete clone;
		cFindDialog->Create(TRUE, stringSelected.c_str(), NULL, FR_DOWN, this->notepannel);
	}
}