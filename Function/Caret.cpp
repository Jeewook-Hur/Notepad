//Caret.cpp
/*
* ���ϸ�Ī:Caret.cpp
* ���:ĳ���� ������ �����Ѵ�.
* �ۼ���:������
* �ۼ�����:2022/7/20 
* ��������:2022/7/21
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
* �Լ���Ī:Caret
* ���:������ ĳ���� ��ǥ�� ���̸� �������� ó������ �ʱ�ȭ�Ѵ�.
*/
Caret::Caret(Notepannel* notepannel) {
	this->notepannel = notepannel;
	this->x = -1;
	this->y = 0;
	this->corX = 0;
	this->corY = 0;
}

/*
* �Լ���Ī:~Caret
* ���:�Ҹ���
*/
Caret::~Caret() {
}

/*
* �Լ���Ī:Create
* ���:ĳ���� �����
*/
void Caret::Create(int width, int height) {
	this->notepannel->CreateSolidCaret(width, height);
}

/*
* �Լ���Ī:Move
* ���:ĳ���� �̵��Ѵ�.
* ��:��ġ�� �Է¹޴� ĳ���� ���� Ŭ���̾�Ʈ ��ǥ�� �̵���Ų��. 
*/
void Caret::Move(int x, int y) { //x��ġ�� y��ġ�� �Է¹޴´�. 
	Glyph* line = NULL;
	Glyph* character = NULL;
	POINT point = { 0,0 };
	int i = 0; //�̱۹���Ʈ ���� ���Ҷ� �ʿ�
	
	//ĳ���� ��ġ ��ǥ�� �����Ѵ�. 
	this->x = x;
	this->y = y;

	//�Է¹��� ��ġ�� ���� �����´�. 
	line = this->notepannel->paper->GetAt(this->y);
	//Ŭ���̾�Ʈ ��ǥ�� ���ΰ��� ���Ѵ�.
	point.x = this->notepannel->characterMatrix->GetLineWidth(line, x) - this->notepannel->clientLocation->x;
#if 0
	order = this->x + 1; // -1���̽� �̹Ƿ� ������ 1 �����ش�. 
	while (i < order) {
		character = line->GetAt(i);
		point.x = point.x + this->notepannel->characterMatrix->GetCharacterWidth(character);
		i++;
	}
#endif
	//���ΰ��� ���Ѵ�.
	//point.y = this->y * this->notepannel->characterMatrix->height;
	point.y = this->notepannel->characterMatrix->GetLineHeight(y) - this->notepannel->clientLocation->lineOrder * this->notepannel->characterMatrix->height;
	//������ �ٷ� �����Ͽ� ��µǾ������ ���ΰ��� ��ĭ ���� �ø���.
	//if (this->notepannel->clientLocation->lastPage == TRUE) {
	//	point.y = point.y + this->notepannel->characterMatrix->height;
	//}

	//ĳ���� ������ Ŭ���̾�Ʈ ��ǥ�� �̵��Ѵ�.
	this->notepannel->SetCaretPos(point);
	//���� ĳ���� ��ǥ�� �����صд�. 
	//�̻��ϰ� CWnd�� GetCaretPos�� �޾ƿ��� ���� ������ �ƴϾ �ε����ϰ� ����. 
	this->corX = point.x;
	this->corY = point.y;
}

/*
* �Լ���Ī:ShowCaret
* ���:ĳ���� ����ȭ�Ѵ�
*/
void Caret::ShowCaret() {
	this->notepannel->ShowCaret();
}

/*
* �Լ���Ī:HideCaret
* ���:ĳ���� �����
*/
void Caret::HideCaret() {
	this->notepannel->HideCaret();
}
