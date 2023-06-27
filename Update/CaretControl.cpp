//CaretControl.cpp
/*
* ���ϸ�Ī:CaretControl.cpp
* ���:ĳ���� �����ϴ� Ŭ����
* �ۼ���:������
* �ۼ�����:2022/8/9
*/
#include "CaretControl.h"
#include "Notepannel.h"
#include "Paper.h"
#include "Line.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Caret.h"
#include "CharacterMatrix.h"

/*
* �Լ���Ī:CaretControl
* ���:������
*/
CaretControl::CaretControl(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CaretControl
* ���:�Ҹ���
*/
CaretControl::~CaretControl() {
}

/*
* �Լ���Ī:Update
* ���:�Է¹��� Ŭ������ �´� ������Ʈ�� �Ѵ�. 
*/
void CaretControl::Update(Subject* theChangedSubject) {
	this->notepannel->isUpdating = TRUE;

	int x;
	int y;
	Glyph* line = 0;
	Glyph* character = 0;

	if (dynamic_cast<Notepannel*>(theChangedSubject)) {//�Է¹��� Ŭ������ �޸����̸�
		//�޸��忡�� ���̿� ���� ���� ��ġ�� �д´�. 
		//���̿��� ���� ���� ��ġ�� ���� �����´�. 
		y = this->notepannel->paper->GetCurrent();
		line = this->notepannel->paper->GetAt(y);
		//�ٿ��� ���� ������ ��ġ�� ���ڸ� �����´�. 
		x = line->GetCurrent();
		if (x != -1) {
			character = line->GetAt(x);
		}
		//���� ������ ũ�⿡ �´� ĳ���� �´� ��ġ�� ����Ѵ�. 
		if (x > -1 && dynamic_cast<DoubleByteCharacter*>(character) && this->notepannel->isComposing == TRUE) { //�������Ʈ�̰� �Է����ϰ��
			//�������Ʈ�ϰ�� ��ġ�� ��ĭ ������ �����Ѵ�. 
			this->notepannel->caret->Move(x - 1, y);
			//�������Ʈ ĳ���� ����Ѵ�.
			this->notepannel->caret->Create(this->notepannel->characterMatrix->GetDoubleByteWidth(), this->notepannel->characterMatrix->height);	
		}
		else {
			//ĳ���� ���� ��ġ�� �̵���Ų��. 
			this->notepannel->caret->Move(x, y);
			//�̱۹���Ʈ ĳ���� ����Ѵ�.
			this->notepannel->caret->Create(2, this->notepannel->characterMatrix->height);
		}
	}
	//this->notepannel->isUpdating = FALSE; //����ǥ���ٿ��� �Ѵ�. 
}
