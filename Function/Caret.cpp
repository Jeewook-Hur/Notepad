//Caret.cpp
/*
* 파일명칭:Caret.cpp
* 기능:캐럿의 정보를 저장한다.
* 작성자:허지욱
* 작성일자:2022/7/20 
* 수정일자:2022/7/21
*/
#include "Notepannel.h"
#include "Caret.h"
#include "Paper.h"
#include "Line.h"
#include "Font.h"
#include "CharacterMatrix.h"
#include "ClientLocation.h"
//#include "afxwin.h"
#include<string>
using namespace std;

/*
* 함수명칭:Caret
* 기능:생성자 캐럿의 좌표를 종이를 기준으로 처음으로 초기화한다.
*/
Caret::Caret(Notepannel* notepannel) {
	this->notepannel = notepannel;
	this->x = -1;
	this->y = 0;
	this->corX = 0;
	this->corY = 0;
}

/*
* 함수명칭:~Caret
* 기능:소멸자
*/
Caret::~Caret() {
}

/*
* 함수명칭:Create
* 기능:캐럿을 만든다
*/
void Caret::Create(int width, int height) {
	this->notepannel->CreateSolidCaret(width, height);
}

/*
* 함수명칭:Move
* 기능:캐럿을 이동한다.
* 상세:위치로 입력받는 캐럿의 값을 클라이언트 좌표로 이동시킨다. 
*/
void Caret::Move(int x, int y) { //x위치와 y위치를 입력받는다. 
	Glyph* line = NULL;
	Glyph* character = NULL;
	POINT point = { 0,0 };
	int i = 0; //싱글바이트 폭을 구할때 필요
	
	//캐럿내 위치 좌표를 갱신한다. 
	this->x = x;
	this->y = y;

	//입력받은 위치의 줄을 가져온다. 
	line = this->notepannel->paper->GetAt(this->y);
	//클라이언트 좌표의 가로값을 구한다.
	point.x = this->notepannel->characterMatrix->GetLineWidth(line, x) - this->notepannel->clientLocation->x;
#if 0
	order = this->x + 1; // -1베이스 이므로 순서는 1 더해준다. 
	while (i < order) {
		character = line->GetAt(i);
		point.x = point.x + this->notepannel->characterMatrix->GetCharacterWidth(character);
		i++;
	}
#endif
	//세로값를 구한다.
	//point.y = this->y * this->notepannel->characterMatrix->height;
	point.y = this->notepannel->characterMatrix->GetLineHeight(y) - this->notepannel->clientLocation->lineOrder * this->notepannel->characterMatrix->height;
	//마지막 줄로 인지하여 출력되었을경우 세로값을 한칸 위로 올린다.
	//if (this->notepannel->clientLocation->lastPage == TRUE) {
	//	point.y = point.y + this->notepannel->characterMatrix->height;
	//}

	//캐럿을 지정한 클라이언트 좌표로 이동한다.
	this->notepannel->SetCaretPos(point);
	//현재 캐럿의 좌표를 저장해둔다. 
	//이상하게 CWnd의 GetCaretPos가 받아오는 값이 정상이 아니어서 부득이하게 쓴다. 
	this->corX = point.x;
	this->corY = point.y;
}

/*
* 함수명칭:ShowCaret
* 기능:캐럿을 가시화한다
*/
void Caret::ShowCaret() {
	this->notepannel->ShowCaret();
}

/*
* 함수명칭:HideCaret
* 기능:캐럿을 숨긴다
*/
void Caret::HideCaret() {
	this->notepannel->HideCaret();
}
