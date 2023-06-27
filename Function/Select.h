//Select.h
/*
* 파일명칭:Select.h
* 기능:선택하기에 관한 기능을 저장하는 헤더
* 작성자:허지욱
* 작성일자:20221014
*/
#ifndef _SELECT_H 
#define _SELECT_H
#define FALSE 0
#define TRUE 1

typedef int BOOL;
class Notepannel;
class Glyph;
class Select {
public:
	Select(Notepannel* notepannel, int previousXIndex = -1, int previousLineOrder = 0, int currentXIndex = -1, int currentLineOrder = 0);
	~Select();
	void MoveCurrent(int currentXIndex, int currentLineOrder);
	BOOL IsSelected(int lineOrder, int charOrder);
	BOOL IsEqual(Glyph* other);
	int previousXIndex;
	int previousLineOrder;
	int currentXIndex; 
	int currentLineOrder;
	//자동조정 하는 부분
	int frontXIndex;
	int frontLineOrder;
	int endXIndex;
	int endLineOrder;
private:
	Notepannel* notepannel;
};

#endif // !_SELECT_H
