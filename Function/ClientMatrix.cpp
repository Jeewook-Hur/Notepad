//ClientMatrix.cpp
/*
* 파일명칭:ClientMatrix.cpp
* 기능:클라이언트의 각종 길이정보를 계산하여 저장하는 파일의 헤더
* 작성자:허지욱
* 작성일자:20220928
*/
#include "ClientMatrix.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "CharacterMatrix.h"
#include "GlyphCreater.h"

/*
* 함수명칭:ClientMatrix
* 기능:생성자
*/
ClientMatrix::ClientMatrix(Notepannel* notepannel) :notepannel(notepannel) {
	WINDOWINFO windowInfo{ 0, };

	//클라이언트의 정보를 가져온다.
	this->notepannel->GetWindowInfo(&windowInfo);

	//클라이언트의 가로세로 길이를 구한다. //마지막 15는 디폴트로 표시되는 스크롤바 크기 빼준거 
	this->width = windowInfo.rcClient.right - windowInfo.rcClient.left - 1 -17;
	this->height = windowInfo.rcClient.bottom - windowInfo.rcClient.top - 1;// -17;

	//클라이언트 안의 줄수를 구한다.
	if (this->notepannel->characterMatrix != NULL) { //패널이 실행되었으면 
		this->lineNumberInPage = this->height / this->notepannel->characterMatrix->height;
	}
	else {
		//패널을 실행중(OnCreate)이면
		this->lineNumberInPage = this->height / 36; //여기서 36은 디폴트 설정 값이다. 
	}
	//필요한 수치를 계산해둔다.
	this->widthOneThird = this->width / 3;
}

/*
* 함수명칭:~ClientMatrix
* 기능:소멸자
*/
ClientMatrix::~ClientMatrix() {

}