//ReplaceCommand.cpp
/*
* 파일명칭:ReplaceCommand.cpp
* 기능:닫기 커멘드
* 작성자:허지욱
* 작성일자:20220826
*/
#include "ReplaceCommand.h"
#include "Notepannel.h"
#include "Paper.h"
#include "Select.h"
#include "Finder.h"
#include "Replacer.h"
#include <afxdlgs.h>
#include<string>
using namespace std;

/*
* 함수명칭:ReplaceCommand
* 기능:생성자
*/
ReplaceCommand::ReplaceCommand(Notepannel* notepannel) : notepannel(notepannel) {
}

/*
* 함수명칭:~ReplaceCommand
* 기능:소멸자
*/
ReplaceCommand::~ReplaceCommand() {
}

/*
* 함수명칭:Execute
* 기능:찾기 커멘드를 실행하다
*/
void ReplaceCommand::Execute() {
	CFindReplaceDialog* cFindDialog = NULL;
	Glyph* clone;
	string stringWritten = this->notepannel->finder->find;
	string stringSelected = "";
	string stringReplace = this->notepannel->replacer->replace;
	//string test = "테스트 문구"; //나중에 찾기클래스의 내용으로 대체 
	Long frontLineOrder = this->notepannel->select->frontLineOrder;
	Long frontCharIndex = this->notepannel->select->frontXIndex;
	Long endLineOrder = this->notepannel->select->endLineOrder;
	Long endCharIndex = this->notepannel->select->endXIndex;

	//찾기바꾸기 공통대화상자를 띄운다. 
	cFindDialog = new CFindReplaceDialog;

	if (this->notepannel->isSelected == FALSE) { //종이에서 선택되어있지 않으면
		//저장된 찾기 내용을 찾기 대화상자의 찾는내용에 적는다. 
		//cFindDialog->Create(TRUE, test.c_str(), NULL, FR_DOWN, this->notepannel);
		cFindDialog->Create(FALSE, stringWritten.c_str(), stringReplace.c_str(), FR_DOWN, this->notepannel);
	}
	else { //종이에서 선택되어 있으면
		//선택된 내용을 찾기대화상자의 찾는내용에 적는다. 
		clone = this->notepannel->paper->Clone(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);
		clone->MergeAllDummyLines();
		stringSelected = clone->GetString();
		delete clone;
		cFindDialog->Create(FALSE, stringSelected.c_str(), stringReplace.c_str(), FR_DOWN, this->notepannel);
	}
}