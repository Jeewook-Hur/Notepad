//ResultFound.cpp
/*
* ���ϸ�Ī:ResultFound.cpp
* ���:�˻������ �����ϰ� �ʿ信 ���� �����ϴ� Ŭ����
* �ۼ���:������
* �ۼ�����:2022/12/14
*/
#include "ResultFound.h"
#include "GlyphCreater.h"
#include "Paper.h"
#include<string>
using namespace std;

/*
* �Լ���Ī:ResultFound
* ���:������
*/
ResultFound::ResultFound(string stringToFind) :stringToFind(stringToFind) {
	GlyphCreater glyphCreater;
	this->paperToFind = 0;
	this->lineOrders = 0;
	this->charIndexes = 0;
	this->count = 0;

	if (this->stringToFind.length() > 0) {
		this->paperToFind = glyphCreater.Create(this->stringToFind);
	}
}

/*
* �Լ���Ī:~ResultFound
* ���:�Ҹ���
*/
ResultFound::~ResultFound() {
	delete[] lineOrders;
	delete[] charIndexes;
	delete paperToFind;
}

Long ResultFound::GetLineOrder(Long index) {
	return this->lineOrders[index];
}

Long ResultFound::GetCharIndex(Long index) {
	return this->charIndexes[index];
}