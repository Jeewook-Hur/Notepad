//ClientLocation.h
/*
* 파일명칭:ClientLocation.h
* 기능:클라이언트의 문서상 가장 좌표를 나타내는 파일의 헤더
* 작성자:허지욱
* 작성일자:20220923
*/
#ifndef _CLIENTLOCATION_H
#define _CLIENTLOCATION_H

typedef int BOOL;
class Notepannel;
class Glyph;
class ClientLocation {
public:
	ClientLocation(Notepannel* notepannel);
	~ClientLocation();
	void Move(int x, int lineOrder);
	//void MoveToCurrent();

	//void MoveBackInPercentage(int percentageX, int percentageY);
	
	//void CheckCaretXIsInside(BOOL* isIn, int* distance);
	//void CheckCaretYIsInside(BOOL* isIn, int* distance);

	//int GetCaretXPercentageInsideClient();
	//int GetCaretYPercentageInsideClient();

	int x;
	int lineOrder;
	//BOOL lastPage;
private:
	Notepannel* notepannel;
};

#endif // !_CLIENTLOCATION_H
