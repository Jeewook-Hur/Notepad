//Zoomer.cpp
/*
* 파일명칭:Zoomer.cpp
* 기능:클라이언트의 배율을 저장하고 변경하는 클래스
* 작성자:허지욱
* 작성일자:2022/10/7
*/
#include "Zoomer.h"

/*
* 함수명칭:Zoomer
* 기능:생성자
*/
Zoomer::Zoomer() {
	this->magnification = 100;
}
Zoomer::Zoomer(int magnification) {
	//1의 자릿수를 내림한다.
	magnification = magnification / 10;
	magnification = magnification * 10;

	//최대 최소 값을 벗어났으면 맞춰준다.
	if (magnification < 10) {
		magnification = 10;
	}
	else if (magnification > 500) {
		magnification = 500;
	}
	this->magnification = magnification;
}

/*
* 함수명칭:~Zoomer
* 기능:소멸자
*/
Zoomer::~Zoomer() {
}

/*
* 함수명칭:Change
* 기능:입력받은 값에 맞게 배율을 설정한다. 10~500의 범위를 갖는다.
*/
int Zoomer::Change(int magnification) {

	//1의 자릿수를 내림한다.
	magnification = magnification / 10;
	magnification = magnification * 10;

	//최대 최소 값을 벗어났으면 맞춰준다.
	if (magnification < 10) {
		magnification = 10;
	}
	else if (magnification > 500) {
		magnification = 500;
	}
	this->magnification = magnification;

	return magnification;
}
