//Zoomer.cpp
/*
* ���ϸ�Ī:Zoomer.cpp
* ���:Ŭ���̾�Ʈ�� ������ �����ϰ� �����ϴ� Ŭ����
* �ۼ���:������
* �ۼ�����:2022/10/7
*/
#include "Zoomer.h"

/*
* �Լ���Ī:Zoomer
* ���:������
*/
Zoomer::Zoomer() {
	this->magnification = 100;
}
Zoomer::Zoomer(int magnification) {
	//1�� �ڸ����� �����Ѵ�.
	magnification = magnification / 10;
	magnification = magnification * 10;

	//�ִ� �ּ� ���� ������� �����ش�.
	if (magnification < 10) {
		magnification = 10;
	}
	else if (magnification > 500) {
		magnification = 500;
	}
	this->magnification = magnification;
}

/*
* �Լ���Ī:~Zoomer
* ���:�Ҹ���
*/
Zoomer::~Zoomer() {
}

/*
* �Լ���Ī:Change
* ���:�Է¹��� ���� �°� ������ �����Ѵ�. 10~500�� ������ ���´�.
*/
int Zoomer::Change(int magnification) {

	//1�� �ڸ����� �����Ѵ�.
	magnification = magnification / 10;
	magnification = magnification * 10;

	//�ִ� �ּ� ���� ������� �����ش�.
	if (magnification < 10) {
		magnification = 10;
	}
	else if (magnification > 500) {
		magnification = 500;
	}
	this->magnification = magnification;

	return magnification;
}
