//CtrlShiftDeleteKey.cpp
/*
* 파일명칭:CtrlShiftDeleteKey.cpp
* 기능:컨트롤 쉬프트 딜리트 키를 눌렀을때의 전략
* 작성자:허지욱
* 작성일자:2022/11/15
*/
#include "CtrlShiftDeleteKey.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "Caret.h"
#include "Document.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"
#include "SelectDelete.h"
#include "CommandCreator.h"
#include "Command.h"
#include "MacroCommand.h"
#include "resource.h"

/*
* 함수명칭:CtrlShiftDeleteKey
* 기능:생성자
*/
CtrlShiftDeleteKey::CtrlShiftDeleteKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~CtrlShiftDeleteKey
* 기능:소멸자
*/
CtrlShiftDeleteKey::~CtrlShiftDeleteKey() {
}

/*
* 함수명칭:OnKeyDown
* 기능:키를 눌렀을때의 이벤트를 실행한다.
*/
void CtrlShiftDeleteKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Glyph* tempLine = NULL;
	Glyph* character = NULL;
	Long paperLength = 0;
	Long lineOrder = -1;
	Long lineLength = -1;
	Long charIndex = -2;
	Long tempOrder = -2;
	Long tempLength = -1;
	Long order = 0;
	Long i = 0;

	paperLength = this->notepannel->paper->GetLength();
	//종이에서 현재 줄의 위치를 찾는다.
	lineOrder = this->notepannel->paper->GetCurrent();
	//종이에서 현재 줄을 가져온다.
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	//현재 줄에서 현재 단어 위치를 가져온다.
	charIndex = currentLine->GetCurrent();
	lineLength = currentLine->GetLength();


	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	if (!(lineOrder >= paperLength - 1 && charIndex >= lineLength - 1) || this->notepannel->isSelected == TRUE) {
		command = commandCreator.Create(IDM_FORMAT_DELETE);
		if (command != NULL) {
			command->Execute();
			this->notepannel->macroCommand->Add(command, 1);
		}
	}
#if 0
	//선택하기를 할당해제한다.
	delete this->notepannel->select;
	//현재위치부터 앞의 단어까지 선택한다.
	this->notepannel->select = new Select(notepannel, charIndex, lineOrder, charIndex, lineOrder);
	if (charIndex < lineLength - 1) {//현재 단어 위치가 맨 마지막이 아니면
		//다음 단어로 이동한다.
		charIndex = currentLine->Last();
		//앞의 단어까지 선택한다. 
		this->notepannel->select->MoveCurrent(charIndex, lineOrder);
	}
	else if (charIndex >= lineLength - 1 && lineOrder < paperLength - 1) {//현재 단어 위치가 맨 마지막이고 현재 줄이 맨 마지막이 아니면
		//앞의 줄로 이동한다.
		lineOrder = this->notepannel->paper->Next();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		//앞의 줄의 끝으로 이동한다. 
		charIndex = currentLine->First();
		//앞의 줄의 끝까지 선택한다. 
		this->notepannel->select->MoveCurrent(charIndex, lineOrder);
	}
#endif

	//문서가 변경되었음을 표시한다. 
	this->notepannel->hasChanged = TRUE;
	//윈도우의 제목을 갱신한다.
	CString windowTitle;
	windowTitle.Format("*%s - Windows 메모장", this->notepannel->document->GetName().c_str());
	this->notepannel->notepad->SetWindowText(windowTitle);

	//선택한 영역을 지운다. 
	SelectDelete selectDelete(this->notepannel);
	selectDelete.OnKeyDown(nChar, nRepCnt, nFlags);
}