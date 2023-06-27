//ResultFound.h
/*
* ���ϸ�Ī:ResultFound.h
* ���:�˻������ �����ϰ� �ʿ信 ���� �����ϴ� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/12/14
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
