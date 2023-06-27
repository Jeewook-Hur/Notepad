//DocumentVirtualSize.cpp
/*
* 파일명칭:DocumentVirtualSize.cpp
* 기능:클라이언트의 문자 크기로 인한 문서의 가상 크기를 구하는 파일
* 작성자:허지욱
* 작성일자:20220923
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
* 함수명칭:DocumentVirtualSize
* 기능:생성자
*/
DocumentVirtualSize::DocumentVirtualSize(Notepannel* notepannel) :notepannel(notepannel) {
	Glyph* currentLine = 0;
	int length;
	int i = 0;
	int lineNumberInPage = this->notepannel->clientMatrix->lineNumberInPage;
	int paperLength = this->notepannel->paper->GetLength();
	int characterHeigth = this->notepannel->characterMatrix->height;

	//배율을 적용한다. 
	characterHeigth = (int)(characterHeigth * 1.0 * this->notepannel->zoomer->magnification / 100);



	this->MaxY = paperLength * characterHeigth;
	this->MaxX = 0;

	while (i < this->notepannel->paper->GetLength()) {//메모장에서 종이의 길이만큼 반복한다. 
		//종이에서 순서의 줄을 가져온다. 
		currentLine = this->notepannel->paper->GetAt(i);
		//줄의 길이를 구한다. 
		length = this->notepannel->characterMatrix->GetLineWidth(currentLine);
		//배율을 적용한다. 
		length = (int)(length * 1.0 * this->notepannel->zoomer->magnification / 100);

		//줄의 길이가 최댓값이면 갱신한다. 
		if (length > this->MaxX) {
			this->MaxX = length;
		}
		i++;
	}

	this->availableX = this->MaxX - this->notepannel->clientMatrix->width;
	if (this->availableX < 0) {
		this->availableX = 0;
	}
	//가능한 줄의 개수를 구한다.
	this->availableLine = paperLength - lineNumberInPage + 1;
	if (this->availableLine < 0 || paperLength <= lineNumberInPage) { //줄의 개수가 음수이면 = 문서의 가상크기가 클라이언트보다 작으면 
		this->availableLine = 0;
	}
}

/*
* 함수명칭:~DocumentVirtualSize
* 기능:소멸자
*/
DocumentVirtualSize::~DocumentVirtualSize() {
}