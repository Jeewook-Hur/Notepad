//PageSetting.h
/*
* 파일명칭:PageSetting.h
* 기능:페이지 설정을 저장하는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/12/19
*/
#ifndef _PAGESETTING_H
#define _PAGESETTING_H
#include<string>
using namespace std;

class Notepannel;
class PageSetting {
public:
	PageSetting(Notepannel* notepannel, string headerString = "", string footerString = "",
		int pageWidth = 210, int pageHeight = 297, int marginLeft = 30, int marginRight = 30, 
		int marginTop = 20, int marginBottom = 15, int headerLength = 15, int footerLength = 15);
	
	~PageSetting();

	int pageWidth;
	int pageHeight;
	int marginLeft;
	int marginRight;
	int marginTop;
	int marginBottom;
	int headerLength;
	int footerLength;
	string documentName;
	string headerString;
	string footerString;

	bool hasFixed;

private:
	Notepannel* notepannel;
};
#endif // !_PAGESETTING_H