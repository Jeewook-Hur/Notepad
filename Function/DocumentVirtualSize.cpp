//DocumentVirtualSize.cpp
/*
* ���ϸ�Ī:DocumentVirtualSize.cpp
* ���:Ŭ���̾�Ʈ�� ���� ũ��� ���� ������ ���� ũ�⸦ ���ϴ� ����
* �ۼ���:������
* �ۼ�����:20220923
*/
#include "DocumentVirtualSize.h"
#include "Notepannel.h"
#include "Paper.h"
//#include "Line.h"
#include "CharacterMatrix.h"
#include "ClientMatrix.h"
#include "GlyphCreater.h"
#include "SingleByteCharacter.h"
#include "Line.h"
#include "Zoomer.h"


/*
* �Լ���Ī:DocumentVirtualSize
* ���:������
*/
DocumentVirtualSize::DocumentVirtualSize(Notepannel* notepannel) :notepannel(notepannel) {
	Glyph* currentLine = 0;
	int length;
	int i = 0;
	int lineNumberInPage = this->notepannel->clientMatrix->lineNumberInPage;
	int paperLength = this->notepannel->paper->GetLength();
	int characterHeigth = this->notepannel->characterMatrix->height;

	//������ �����Ѵ�. 
	characterHeigth = (int)(characterHeigth * 1.0 * this->notepannel->zoomer->magnification / 100);



	this->MaxY = paperLength * characterHeigth;
	this->MaxX = 0;

	while (i < this->notepannel->paper->GetLength()) {//�޸��忡�� ������ ���̸�ŭ �ݺ��Ѵ�. 
		//���̿��� ������ ���� �����´�. 
		currentLine = this->notepannel->paper->GetAt(i);
		//���� ���̸� ���Ѵ�. 
		length = this->notepannel->characterMatrix->GetLineWidth(currentLine);
		//������ �����Ѵ�. 
		length = (int)(length * 1.0 * this->notepannel->zoomer->magnification / 100);

		//���� ���̰� �ִ��̸� �����Ѵ�. 
		if (length > this->MaxX) {
			this->MaxX = length;
		}
		i++;
	}

	this->availableX = this->MaxX - this->notepannel->clientMatrix->width;
	if (this->availableX < 0) {
		this->availableX = 0;
	}
	//������ ���� ������ ���Ѵ�.
	this->availableLine = paperLength - lineNumberInPage + 1;
	if (this->availableLine < 0 || paperLength <= lineNumberInPage) { //���� ������ �����̸� = ������ ����ũ�Ⱑ Ŭ���̾�Ʈ���� ������ 
		this->availableLine = 0;
	}
}

/*
* �Լ���Ī:~DocumentVirtualSize
* ���:�Ҹ���
*/
DocumentVirtualSize::~DocumentVirtualSize() {
}