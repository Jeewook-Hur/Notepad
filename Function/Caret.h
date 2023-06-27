//Caret.h
/*
* 파일명칭:Caret.h
* 기능:캐럿의 정보를 저장하는 헤더 어떤 글꼴이어도 캐럿이 기능하게 한다.
* 작성자:허지욱
* 작성일자:2022/7/20
*/
#ifndef _CARET_H
#define _CARET_H
//#include<afxwin.h>

//순서좌표 - 순서를 기준으로 한 좌표 - 사실상 종이와 연동되어있다. 
//클라이언트좌표 - 픽셀을 기준으로 한 좌표 - 글꼴에 따라 변동된다.

class Notepannel;
class Glyph;
class Caret {
public:
	Caret(Notepannel* notepannel);
	~Caret();
	void Create(int width, int height);
	void Move(int x, int y);
	void ShowCaret();
	void HideCaret();

	//순서좌표
	//캐럿의 순서를 기준으로 한 좌표
	int x; //-1이 시작
	int y; //줄은 항상 있으므로 0이 시작
	int corX;
	int corY;
private:
	Notepannel* notepannel;

};
#endif // !_CARET_H