//CaretControl.cpp
/*
* 파일명칭:CaretControl.cpp
* 기능:캐럿을 조정하는 클래스
* 작성자:허지욱
* 작성일자:2022/8/9
*/
#include "CaretControl.h"
#include "Notepannel.h"
#include "Paper.h"
#include "Line.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Caret.h"
#include "CharacterMatrix.h"

/*
* 함수명칭:CaretControl
* 기능:생성자
*/
CaretControl::CaretControl(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~CaretControl
* 기능:소멸자
*/
CaretControl::~CaretControl() {
}

/*
* 함수명칭:Update
* 기능:입력받은 클래스에 맞는 업데이트를 한다. 
*/
void CaretControl::Update(Subject* theChangedSubject) {
	this->notepannel->isUpdating = TRUE;

	int x;
	int y;
	Glyph* line = 0;
	Glyph* character = 0;

	if (dynamic_cast<Notepannel*>(theChangedSubject)) {//입력받은 클래스가 메모장이면
		//메모장에서 종이와 줄의 현재 위치를 읽는다. 
		//종이에서 현재 줄의 위치와 줄을 가져온다. 
		y = this->notepannel->paper->GetCurrent();
		line = this->notepannel->paper->GetAt(y);
		//줄에서 현재 글자의 위치와 글자를 가져온다. 
		x = line->GetCurrent();
		if (x != -1) {
			character = line->GetAt(x);
		}
		//현재 글자의 크기에 맞는 캐럿를 맞는 위치에 출력한다. 
		if (x > -1 && dynamic_cast<DoubleByteCharacter*>(character) && this->notepannel->isComposing == TRUE) { //더블바이트이고 입력중일경우
			//더블바이트일경우 위치를 한칸 앞으로 조정한다. 
			this->notepannel->caret->Move(x - 1, y);
			//더블바이트 캐럿을 출력한다.
			this->notepannel->caret->Create(this->notepannel->characterMatrix->GetDoubleByteWidth(), this->notepannel->characterMatrix->height);	
		}
		else {
			//캐럿을 현재 위치로 이동시킨다. 
			this->notepannel->caret->Move(x, y);
			//싱글바이트 캐럿을 출력한다.
			this->notepannel->caret->Create(2, this->notepannel->characterMatrix->height);
		}
	}
	//this->notepannel->isUpdating = FALSE; //상태표시줄에서 한다. 
}
