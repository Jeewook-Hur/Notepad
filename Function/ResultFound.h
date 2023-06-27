//ResultFound.h
/*
* 파일명칭:ResultFound.h
* 기능:검색결과를 저장하고 필요에 따라 변경하는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/12/14
*/
#ifndef _FINDRESULT_H
#define _FINDRESULT_H
#include<string>
using namespace std;

typedef signed long int Long;

class Glyph;
class ResultFound {
public:
	ResultFound(string stringToFind = "");
	~ResultFound();
	Long GetLineOrder(Long index);
	Long GetCharIndex(Long index);
	string stringToFind;
	Glyph* paperToFind;
	Long(*lineOrders);
	Long(*charIndexes);
	Long count;

};




#endif // !_FINDRESULT_H
