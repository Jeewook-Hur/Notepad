//ResultFound.cpp
/*
* 파일명칭:ResultFound.cpp
* 기능:검색결과를 저장하고 필요에 따라 변경하는 클래스
* 작성자:허지욱
* 작성일자:2022/12/14
*/
#include "ResultFound.h"
#include "GlyphCreater.h"
#include "Paper.h"
#include<string>
using namespace std;

/*
* 함수명칭:ResultFound
* 기능:생성자
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
* 함수명칭:~ResultFound
* 기능:소멸자
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