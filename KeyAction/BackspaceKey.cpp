//BackspaceKey.cpp
/*
* 파일명칭:BackspaceKey.cpp
* 기능:백스페이스키를 눌렀을때의 이벤트
* 작성자:허지욱
* 작성일자:2022/9/16
*/
#include "BackspaceKey.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "resource.h"
#include "CommandCreator.h"
#include "Command.h"
#include "MacroCommand.h"
#include "Document.h"

/*
* 함수명칭:BackspaceKey
* 기능:생성자
*/
BackspaceKey::BackspaceKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~BackspaceKey
* 기능:소멸자
*/
BackspaceKey::~BackspaceKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void BackspaceKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {	
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	Glyph* currentLine = NULL;
	Glyph* tempLine = NULL;
	Glyph* character = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long tempOrder = -2;
	Long tempLength = -1;
	Long order = 0;
	Long i = 0;
	UINT lineWrapState = -1;


	command = commandCreator.Create(VK_BACK, 0, 0);
	if (command != NULL) {
		command->Execute();
		this->notepannel->macroCommand->Add(command, 1);
	}

	int charNumber = this->notepannel->paper->GetCharNumber();

	if (this->notepannel->macroCommand->savePoint == 0 && charNumber > 0) {
		//문서가 변경되었음을 표시한다. 
		this->notepannel->hasChanged = TRUE;

		//윈도우의 제목을 갱신한다.
		CString windowTitle;
		windowTitle.Format("*%s - Windows 메모장", this->notepannel->document->GetName().c_str());
		this->notepannel->notepad->SetWindowText(windowTitle);
	}
	else if (this->notepannel->macroCommand->savePoint == 0 && charNumber <= 0) {
		this->notepannel->hasChanged = FALSE;
		//윈도우의 제목을 갱신한다.
		CString windowTitle;
		windowTitle.Format("%s - Windows 메모장", this->notepannel->document->GetName().c_str());
		this->notepannel->notepad->SetWindowText(windowTitle);
	}

	this->notepannel->documentUploaded = TRUE;
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//delete키의 경우 호출을 안하기에 호출함수가 필요하다. 
	this->notepannel->Invalidate(TRUE);
	//캐럿을 보이게한다.
	this->notepannel->caret->ShowCaret();

#if 0
	//종이에서 현재 줄의 위치를 찾는다.
	lineOrder = this->notepannel->paper->GetCurrent();
	//종이에서 현재 줄을 가져온다.
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	//현재 줄에서 현재 단어 위치를 가져온다.
	charIndex = currentLine->GetCurrent();
	if (charIndex > -1) {//현재 단어 위치가 맨 처음이 아니면
		//단어 위치 앞의 순서의 단어를 지운다.
		currentLine->Remove(charIndex);
	}
	else if (charIndex <= -1 && lineOrder > 0) {//현재 단어 위치가 맨 처음이고 현재 줄이 맨 처음이 아니면
		//현재 줄을 기억한다.
		tempLine = currentLine->Clone();
		//현재 줄을 지운다.
		this->notepannel->paper->Remove(lineOrder);
		//바뀐 현재 줄을 가져온다.
		lineOrder = this->notepannel->paper->GetCurrent();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		//이전 줄의 맨뒤로 이동한다.
		//줄의 현재 위치를 기억한다.
		tempOrder = currentLine->Last();

		tempLength = tempLine->GetLength();
		while (i < tempLength) {//기억한 줄의 길이만큼 반복한다.
			//줄에 기억한 줄의 글자의 복사본을 붙여쓴다.
			character = tempLine->GetAt(order);
			order++;
			currentLine->Add(character->Clone());
			i++;
		}
		//줄에서 기억한 단어위치로 이동한다.
		currentLine->Move(tempOrder);
		//기억한 줄을 제거한다.
		delete tempLine;

		lineWrapState = this->notepannel->cMenu.GetMenuState(IDM_FORMAT_LINEWRAP, MF_BYCOMMAND);
		if (lineWrapState == MF_CHECKED && tempOrder > -1) { //자동개행기능이 켜져있고 합친줄의 맨앞이 아니면
			//한글자 더 지운다. 
			currentLine->Remove(tempOrder);
		}
	}

	//문서가 변경되었음을 표시한다. 
	this->notepannel->documentUploaded = TRUE;
	//클라이언트의 자동이동이 필요한지 체크한다. 
	this->notepannel->clientMoveCheck = TRUE;
	//업데이트 갱신 함수를 호출한다.
	this->notepannel->Notify();
#endif
}