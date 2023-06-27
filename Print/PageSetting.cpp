//PageSetting.cpp
/*
* 파일명칭:PageSetting.cpp
* 기능:페이지 설정을 저장하는 클래스
* 작성자:허지욱
* 작성일자:2022/12/19
*/
#include "PageSetting.h"

/*
* 함수명칭:PageSetting
* 기능:생성자
*/
PageSetting::PageSetting(Notepannel* notepannel, string headerString, string footerString, 
	int pageWidth, int pageHeight, int marginLeft, int marginRight,
	int marginTop, int marginBottom, int headerLength, int footerLength)
	:notepannel(notepannel), headerString(headerString), footerString(footerString) {
	this->pageWidth = pageWidth;
	this->pageHeight = pageHeight;
	this->marginLeft = marginLeft;
	this->marginRight = marginRight;
	this->marginTop = marginTop;
	this->marginBottom = marginBottom;
	this->headerLength = headerLength;
	this->footerLength = footerLength;
	this->hasFixed = false;

	//입력된 여백이 가로 길이보다 크면
	if (pageWidth <= marginLeft + marginRight) {
		this->hasFixed = true;
		this->marginLeft = 30;
		this->marginRight = 30;
	}

	//입력된 여백이 세로 길이보다 크면
	if (pageHeight <= marginTop + marginBottom + headerLength + footerLength) {
		this->hasFixed = true;
		this->marginTop = 20;
		this->marginBottom = 15;
		this->headerLength = 15;
		this->footerLength = 15;
	}

	//입력된 여백중 음수 값이 있으면 디폴트 값으로 설정해준다. 
	if (marginLeft < 0) { 
		this->hasFixed = true;
		this->marginLeft = 30;
	}
	if (marginRight < 0) { 
		this->hasFixed = true;
		this->marginRight = 30;
	}
	if (marginTop < 0) { 
		this->hasFixed = true;
		this->marginTop = 20;
	}
	if (marginBottom < 0) { 
		this->hasFixed = true;
		this->marginBottom = 15;
	}
	if (headerLength < 0) { 
		this->hasFixed = true;
		this->headerLength = 15;
	}
	if (footerLength < 0) { 
		this->hasFixed = true;
		this->footerLength = 15;
	}
}

/*
* 함수명칭:~PageSetting
* 기능:소멸자
*/
PageSetting::~PageSetting() {
}