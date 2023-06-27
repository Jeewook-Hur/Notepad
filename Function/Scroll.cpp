//Scroll.cpp
/*
* 파일명칭:Scroll.cpp
* 기능:스크롤의 정보를 갱신하는 함수의 헤더
* 작성자:허지욱
* 작성일자:20220929
*/
#include "Scroll.h"
#include "Notepannel.h"
#include "DocumentVirtualSize.h"
#include "ClientMatrix.h"
#include "Paper.h"
//#include "ClientLocation.h"

/*
* 함수명칭:Scroll
* 기능:생성자
*/
Scroll::Scroll(Notepannel* notepannel):notepannel(notepannel) {
	SCROLLINFO scrollInfo = { 0, };
	int scrollMaxRange;
	
	this->notepannel->isScrollSetting = TRUE;
	
	scrollInfo = { sizeof(SCROLLINFO), SIF_ALL, 0, 0, 0, 0, 0 };
	
	//세로 스크롤
	//세로 스크롤의 기본정보 설정
	this->pageSizeY = (UINT)(this->notepannel->clientMatrix->lineNumberInPage);
	scrollMaxRange = this->notepannel->paper->GetLength() - 1;
	
	//scrollInfo.nPage = this->pageSizeY;

	if (this->notepannel->documentVirtualSize->availableLine <= 0) {
		scrollInfo.fMask = SIF_DISABLENOSCROLL;
	}

	scrollInfo.nPage = this->pageSizeY;
	scrollInfo.nMax = scrollMaxRange;
	this->maxY = scrollMaxRange - this->pageSizeY;
	
	scrollInfo.fMask = SIF_ALL;

	if (this->notepannel->documentVirtualSize->availableLine <= 0) {
		scrollInfo.fMask = SIF_DISABLENOSCROLL;
	}

	this->notepannel->SetScrollInfo(SB_VERT, &scrollInfo);

	//가로 스크롤
	//가로 스크롤 기본정보 설정
	scrollInfo.fMask = SIF_ALL;

	this->pageSizeX = (UINT)(this->notepannel->clientMatrix->width);
	scrollMaxRange = this->notepannel->documentVirtualSize->MaxX;
	scrollInfo.nPage = this->pageSizeX;
	scrollInfo.nMax = scrollMaxRange;
	this->maxX = scrollMaxRange - this->pageSizeX;

	if (this->notepannel->documentVirtualSize->availableX <= 0) {
		scrollInfo.fMask = SIF_DISABLENOSCROLL;
	}

	this->notepannel->SetScrollInfo(SB_HORZ, &scrollInfo);

	if (this->notepannel->documentVirtualSize->availableLine > 0 && this->notepannel->documentVirtualSize->availableX > 0) {
		this->notepannel->EnableScrollBar(SB_BOTH, ESB_ENABLE_BOTH);
	}
	else if (this->notepannel->documentVirtualSize->availableLine > 0 && this->notepannel->documentVirtualSize->availableX <= 0) {
		this->notepannel->EnableScrollBar(SB_VERT, ESB_ENABLE_BOTH);
		this->notepannel->EnableScrollBar(SB_HORZ, ESB_DISABLE_BOTH);
	}
	else if (this->notepannel->documentVirtualSize->availableLine <= 0 && this->notepannel->documentVirtualSize->availableX > 0) {
		this->notepannel->EnableScrollBar(SB_HORZ, ESB_ENABLE_BOTH);
		this->notepannel->EnableScrollBar(SB_VERT, ESB_DISABLE_BOTH);
	}
	else if (this->notepannel->documentVirtualSize->availableLine <= 0 && this->notepannel->documentVirtualSize->availableX <= 0) {
		this->notepannel->EnableScrollBar(SB_BOTH, ESB_DISABLE_BOTH);
	}

#if 0
	//세로 스크롤을 사용 여부 설정
	if (this->notepannel->documentVirtualSize->availableLine > 0) {
		this->notepannel->EnableScrollBar(SB_VERT, ESB_ENABLE_BOTH);
	}
	else {
		this->notepannel->EnableScrollBar(SB_VERT, ESB_DISABLE_BOTH);
	}

	//가로 스크롤 사용 여부 설정
	if (this->notepannel->documentVirtualSize->availableX > 0) {
		this->notepannel->EnableScrollBar(SB_HORZ, ESB_ENABLE_BOTH);
	}
	else {
		this->notepannel->EnableScrollBar(SB_HORZ, ESB_DISABLE_BOTH);
	}
#endif
	
	this->notepannel->ShowScrollBar(SB_VERT);
	this->notepannel->ShowScrollBar(SB_HORZ);

	this->notepannel->isScrollSetting = FALSE;

}

/*
* 함수명칭:~Scroll
* 기능:소멸자
*/
Scroll::~Scroll() {
}

/*
* 함수명칭:Move
* 기능:입력받은 위치로 스크롤을 이동시킨다. 
*/
void Scroll::Move(int x, int lineOrder) {
	this->notepannel->SetScrollPos(SB_HORZ, x);
	this->notepannel->SetScrollPos(SB_VERT, lineOrder);
}

#if 0
/*
* 함수명칭:MoveToClientLocation
* 기능:클라이언트와 같은 위치로 이동한다. 
*/
void Scroll::MoveToClientLocation() {
	this->notepannel->SetScrollPos(SB_HORZ, this->notepannel->clientLocation->x );
	this->notepannel->SetScrollPos(SB_VERT, this->notepannel->clientLocation->lineOrder);
}
#endif
