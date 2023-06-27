//Scroll.cpp
/*
* ���ϸ�Ī:Scroll.cpp
* ���:��ũ���� ������ �����ϴ� �Լ��� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#include "Scroll.h"
#include "Notepannel.h"
#include "DocumentVirtualSize.h"
#include "ClientMatrix.h"
#include "Paper.h"
//#include "ClientLocation.h"

/*
* �Լ���Ī:Scroll
* ���:������
*/
Scroll::Scroll(Notepannel* notepannel):notepannel(notepannel) {
	SCROLLINFO scrollInfo = { 0, };
	int scrollMaxRange;
	
	this->notepannel->isScrollSetting = TRUE;
	
	scrollInfo = { sizeof(SCROLLINFO), SIF_ALL, 0, 0, 0, 0, 0 };
	
	//���� ��ũ��
	//���� ��ũ���� �⺻���� ����
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

	//���� ��ũ��
	//���� ��ũ�� �⺻���� ����
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
	//���� ��ũ���� ��� ���� ����
	if (this->notepannel->documentVirtualSize->availableLine > 0) {
		this->notepannel->EnableScrollBar(SB_VERT, ESB_ENABLE_BOTH);
	}
	else {
		this->notepannel->EnableScrollBar(SB_VERT, ESB_DISABLE_BOTH);
	}

	//���� ��ũ�� ��� ���� ����
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
* �Լ���Ī:~Scroll
* ���:�Ҹ���
*/
Scroll::~Scroll() {
}

/*
* �Լ���Ī:Move
* ���:�Է¹��� ��ġ�� ��ũ���� �̵���Ų��. 
*/
void Scroll::Move(int x, int lineOrder) {
	this->notepannel->SetScrollPos(SB_HORZ, x);
	this->notepannel->SetScrollPos(SB_VERT, lineOrder);
}

#if 0
/*
* �Լ���Ī:MoveToClientLocation
* ���:Ŭ���̾�Ʈ�� ���� ��ġ�� �̵��Ѵ�. 
*/
void Scroll::MoveToClientLocation() {
	this->notepannel->SetScrollPos(SB_HORZ, this->notepannel->clientLocation->x );
	this->notepannel->SetScrollPos(SB_VERT, this->notepannel->clientLocation->lineOrder);
}
#endif
