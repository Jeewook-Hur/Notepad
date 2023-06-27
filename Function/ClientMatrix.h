//ClientMatrix.h
/*
* 파일명칭:ClientMatrix.h
* 기능:클라이언트의 각종 길이정보를 계산하여 저장하는 파일의 헤더
* 작성자:허지욱
* 작성일자:20220928
*/
#ifndef _CLIENTMATRIX_H
#define _CLIENTMATRIX_H

class Notepannel;
class ClientMatrix {
public:
	ClientMatrix(Notepannel* notepannel);
	~ClientMatrix();

	int width;
	int height;
	int lineNumberInPage;
	int widthOneThird;

private:
	Notepannel* notepannel;
};

#endif // !_CLIENTMATRIX_H
