//PageSetting.cpp
/*
* ���ϸ�Ī:PageSetting.cpp
* ���:������ ������ �����ϴ� Ŭ����
* �ۼ���:������
* �ۼ�����:2022/12/19
*/
#include "PageSetting.h"

/*
* �Լ���Ī:PageSetting
* ���:������
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

	//�Էµ� ������ ���� ���̺��� ũ��
	if (pageWidth <= marginLeft + marginRight) {
		this->hasFixed = true;
		this->marginLeft = 30;
		this->marginRight = 30;
	}

	//�Էµ� ������ ���� ���̺��� ũ��
	if (pageHeight <= marginTop + marginBottom + headerLength + footerLength) {
		this->hasFixed = true;
		this->marginTop = 20;
		this->marginBottom = 15;
		this->headerLength = 15;
		this->footerLength = 15;
	}

	//�Էµ� ������ ���� ���� ������ ����Ʈ ������ �������ش�. 
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
* �Լ���Ī:~PageSetting
* ���:�Ҹ���
*/
PageSetting::~PageSetting() {
}