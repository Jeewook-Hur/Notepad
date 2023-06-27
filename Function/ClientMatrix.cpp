//ClientMatrix.cpp
/*
* ���ϸ�Ī:ClientMatrix.cpp
* ���:Ŭ���̾�Ʈ�� ���� ���������� ����Ͽ� �����ϴ� ������ ���
* �ۼ���:������
* �ۼ�����:20220928
*/
#include "ClientMatrix.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "CharacterMatrix.h"
#include "GlyphCreater.h"

/*
* �Լ���Ī:ClientMatrix
* ���:������
*/
ClientMatrix::ClientMatrix(Notepannel* notepannel) :notepannel(notepannel) {
	WINDOWINFO windowInfo{ 0, };

	//Ŭ���̾�Ʈ�� ������ �����´�.
	this->notepannel->GetWindowInfo(&windowInfo);

	//Ŭ���̾�Ʈ�� ���μ��� ���̸� ���Ѵ�. //������ 15�� ����Ʈ�� ǥ�õǴ� ��ũ�ѹ� ũ�� ���ذ� 
	this->width = windowInfo.rcClient.right - windowInfo.rcClient.left - 1 -17;
	this->height = windowInfo.rcClient.bottom - windowInfo.rcClient.top - 1;// -17;

	//Ŭ���̾�Ʈ ���� �ټ��� ���Ѵ�.
	if (this->notepannel->characterMatrix != NULL) { //�г��� ����Ǿ����� 
		this->lineNumberInPage = this->height / this->notepannel->characterMatrix->height;
	}
	else {
		//�г��� ������(OnCreate)�̸�
		this->lineNumberInPage = this->height / 36; //���⼭ 36�� ����Ʈ ���� ���̴�. 
	}
	//�ʿ��� ��ġ�� ����صд�.
	this->widthOneThird = this->width / 3;
}

/*
* �Լ���Ī:~ClientMatrix
* ���:�Ҹ���
*/
ClientMatrix::~ClientMatrix() {

}