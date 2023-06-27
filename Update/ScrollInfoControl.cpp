//ScrollInfoControl.cpp
/*
* 파일명칭:ScrollInfoControl.cpp
* 기능:스크롤의 설정을 조정하는 클래스
* 작성자:허지욱
* 작성일자:2022/9/29
*/
#include "ScrollInfoControl.h"
#include "Notepannel.h"
#include "Scroll.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"

/*
* 함수명칭:ScrollInfoControl
* 기능:생성자
*/
ScrollInfoControl::ScrollInfoControl(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~ScrollInfoControl
* 기능:소멸자
*/
ScrollInfoControl::~ScrollInfoControl() {
}

/*
* 함수명칭:Update
* 기능:입력받은 클래스에 맞는 업데이트를 한다.
*/
void ScrollInfoControl::Update(Subject* theChangedSubject) {
	this->notepannel->isUpdating = TRUE;

	int vScrollPosition;
	int hScrollPosition;

	if (dynamic_cast<Notepannel*>(theChangedSubject)) {//입력받은 클래스가 메모장이면
		if (this->notepannel->documentUploaded == TRUE) { //문서를 작성중이었으면
			//스크롤의 현재 위치를 구한다. 
			vScrollPosition = this->notepannel->GetScrollPos(SB_VERT);
			hScrollPosition = this->notepannel->GetScrollPos(SB_HORZ);
			//스크롤을 갱신 및 초기화 한다.
			delete this->notepannel->scroll;
			this->notepannel->scroll = new Scroll(this->notepannel);
			//스크롤의 길이가 줄어들었으면 기억된 위치를 갱신한다. 
			if (vScrollPosition > this->notepannel->scroll->maxY) {
				vScrollPosition = this->notepannel->scroll->maxY;
				this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder - this->notepannel->clientMatrix->lineNumberInPage + 1);
				//this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, 999999);
				//this->notepannel->scroll->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);
			}
			if (hScrollPosition > this->notepannel->scroll->maxX) {
				hScrollPosition = this->notepannel->scroll->maxX;
				this->notepannel->clientLocation->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);
				//this->notepannel->clientLocation->Move(999999, this->notepannel->clientLocation->lineOrder);
				//this->notepannel->scroll->Move(this->notepannel->clientLocation->x, this->notepannel->clientLocation->lineOrder);
			}
			//스크롤을 기억된 위치로 이동시킨다. 
			this->notepannel->SetScrollPos(SB_VERT, vScrollPosition);
			this->notepannel->SetScrollPos(SB_HORZ, hScrollPosition);
			//문서 변동 플래그를 내린다. 
			this->notepannel->documentUploaded = FALSE;
		}
	}
	this->notepannel->isUpdating = FALSE;
}
