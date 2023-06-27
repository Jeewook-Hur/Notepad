//Zoomer.h
/*
* 파일명칭:Zoomer.h
* 기능:클라이언트의 배율을 저장하고 변경하는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/10/7
*/
#ifndef _ZOOMER_H
#define _ZOOMER_H

class Zoomer {
public:
	Zoomer();
	Zoomer(int magnification);
	~Zoomer();
	int Change(int magnification);
	int magnification; // 10~500의 범위를 갖는다.
};

#endif // !_ZOOMER_H
