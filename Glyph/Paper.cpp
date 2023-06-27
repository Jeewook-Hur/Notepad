//Paper.cpp
/*
* 파일명칭:Paper.cpp
* 기능:종이
* 작성자:허지욱
* 작성일자:2022/7/11
*/
#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "GlyphCreater.h"
#include "Visitor.h"
#include<string>
using namespace std;

/*
* 함수명칭:Paper
* 기능:생성자
*/
Paper::Paper(Long capacity) :Composite(capacity) {
}
Paper::Paper(const Paper& source) : Composite(source) {
}

/*
* 함수명칭:~Paper
* 기능:소멸자
*/
Paper::~Paper() {
}

/*
* 함수명칭:Add
* 기능:입력한 위치에 입력한 종이를 더한다.
*/
Long Paper::Add(Glyph* paperToAdd, Long lineOrder, Long charIndex) { //입력할 종이, 입력할 위치를 입력받는다. 
	Glyph* currentLine = 0;
	Glyph* endLine = 0;
	Glyph* nextLine = 0;
	Glyph* lastLine = 0;
	Glyph* clone = 0;
	Long paperLength = -1;
	Long endLineOrder = -1;
	Long endCharIndex = -2;
	Long currentLineLength = -1;
	Long lastLineLength = -1;

	//기존 종이에 입력한 종이를 입력할 위치 다음줄 부터 입력한다. 
	Composite::Add(paperToAdd, lineOrder + 1);

	//넣은 종이의 길이를 구한다.
	paperLength = paperToAdd->GetLength();
	//넣은 좋이가 들어간 종이의 새종이의 마지막 줄을 구한다. 
	endLineOrder = lineOrder + paperLength;
	
	//입력할 위치의 줄을 가져온다. 
	currentLine = Composite::GetAt(lineOrder);
	//현재 줄의 길이를 가져온다. 
	currentLineLength = currentLine->GetLength();

	if (charIndex < currentLineLength - 1) {//현재 줄의 입력 위치가 맨뒤가 아니면
		//줄의 클론을 만든다.
		clone = currentLine->Clone();
		//현재 줄의 현재 위치부터 끝까지 제거한다.
		currentLine->Remove(charIndex + 1, currentLineLength - 1);
		//클론 줄의 처음부터 현재 위치까지 제거한다.
		clone->Remove(0, charIndex);
		//클론 줄을 종이에 넣은 새 종이 부분의 마지막 줄에 넣는다.	
		endLine = Composite::GetAt(endLineOrder);
		currentLineLength = endLine->GetLength();
		endLine->Add(clone, currentLineLength);
		//클론 줄을 할당해제한다.
		delete clone;
	}
	//현재 줄과 다음줄을 병합한다.
	nextLine = Composite::GetAt(lineOrder + 1);
	//lineLength = currentLine->GetLength();
	currentLine->Add(nextLine, charIndex + 1);
	Composite::Remove(lineOrder + 1);
	//마지막 줄의 위치를 갱신한다. 
	endLineOrder--;

	lastLine = paperToAdd->GetAt(paperToAdd->GetCurrent());
	lastLineLength = lastLine->GetLength();
	if (endLineOrder != lineOrder) {//마지막 줄이 현재 줄과 일치하지 않으면
		//삽입한 줄의 마지막 줄의 마지막 순서를 구한다. 
		endCharIndex = lastLineLength - 1;
	}
	else {
		//현재줄의 붙여넣기 이후 위치를 구한다. 
		endCharIndex = charIndex + lastLineLength;
	}

	lineOrder = Composite::Move(endLineOrder);
	currentLine = Composite::GetAt(lineOrder);
	currentLine->Move(endCharIndex);

	return lineOrder;
}

/*
* 함수명칭:Remove
* 기능:입력받은 범위를 제거한다. 
*/
Long Paper::Remove(Long startLineOrder, Long startCharIndex, Long endLineOrder, Long endCharIndex) {
	Glyph* startLine = 0;
	Glyph* endLine = 0;
	Long length = -1;

	//맨 앞줄을 가져온다. 
	startLine = Composite::GetAt(startLineOrder);
	if (startLineOrder == endLineOrder) {//현재줄이 앞줄과 같으면 
		startLine->Remove(startCharIndex + 1, endCharIndex);
	}
	else {//현재줄과 앞줄이 다르면
		//맨 앞줄에서 지울 부문을 지운다.
		length = startLine->GetLength();
		startLine->Remove(startCharIndex + 1, length - 1);
		//맨 뒷줄의 지울 부분을 지운다.
		endLine = Composite::GetAt(endLineOrder);
		endLine->Remove(0, endCharIndex);
		//맨 앞줄에 맨 뒷줄을 붙인다. 
		startLine->Add(endLine, startCharIndex + 1);
		//두번재 줄부터 마지막 줄까지 지운다.
		Composite::Remove(startLineOrder + 1, endLineOrder);
	}
	//시작줄의 시작 위치로 이동한다.
	Long lineOrder;
	lineOrder = Composite::Move(startLineOrder);
	startLine = Composite::GetAt(lineOrder);
	startLine->Move(startCharIndex);

	return lineOrder;
}

/*
* 함수명칭:FindChar
* 기능:입력받은 글자를 찾는다. 
*/
void Paper::FindChar(Glyph* characterToFind, Long*(*lineOrders), Long*(*charOrders), Long* count) {//글자를 입력받는다. 
	//종이의 글자 수를 계산한다. 
	Long charNumber = this->GetCharNumber();
	Glyph* currentLine = 0;
	Glyph* characterInPaper = 0;
	Long lineOrder = 0;
	Long paperLength = Composite::GetLength();
	Long lineLength;
	Long charOrder;
	BOOL result;
	Long i = 0;
	
	//글자 수 크기의 배열을 만든다. 
	*lineOrders = new Long[charNumber];
	*charOrders = new Long[charNumber];
	//개수를 초기화한다. 
	*count = 0;

	while (lineOrder < paperLength) {
		currentLine = Composite::GetAt(lineOrder);
		lineLength = currentLine->GetLength();
		charOrder = 0;
		while (charOrder < lineLength) {
			characterInPaper = currentLine->GetAt(charOrder);
			//글자의 자료형에 맞게 일치하는지 확인한다.
			result = 0; //초기화
			result = characterInPaper->IsEqual(characterToFind);
			//일치하면
			if (result == 1 && i < charNumber) { //찾았으면 
				//현재 위치를 기록한다.
				(*lineOrders)[i] = lineOrder;
				(*charOrders)[i] = charOrder;
				(*count)++;
				i++;
			}
			charOrder++;
		}
		lineOrder++;
	}
}//찾은 내용을 반환한다. 

/*
* 함수명칭:FindCharUpperLower
* 기능:입력받은 문자의 싱글바이트를 대소문자 구분없이 검색한다. 
*/
void Paper::FindCharUpperLower(Glyph* characterToFind, Long* (*lineOrders), Long* (*charOrders), Long* count) {//글자를 입력받는다. 
	//종이의 글자 수를 계산한다. 
	Long charNumber = this->GetCharNumber();
	Glyph* currentLine = 0;
	Glyph* characterInPaper = 0;
	Long lineOrder = 0;
	Long paperLength = Composite::GetLength();
	Long lineLength;
	Long charOrder;
	BOOL result;
	Long i = 0;

	//글자 수 크기의 배열을 만든다. 
	*lineOrders = new Long[charNumber];
	*charOrders = new Long[charNumber];
	//개수를 초기화한다. 
	*count = 0;

	while (lineOrder < paperLength) {
		currentLine = Composite::GetAt(lineOrder);
		lineLength = currentLine->GetLength();
		charOrder = 0;
		while (charOrder < lineLength) {
			characterInPaper = currentLine->GetAt(charOrder);
			//글자의 자료형에 맞게 일치하는지 확인한다.
			result = 0; //초기화
			result = characterInPaper->IsEqualUpperLower(characterToFind);
			//일치하면
			if (result == 1 && i < charNumber) { //찾았으면 
				//현재 위치를 기록한다.
				(*lineOrders)[i] = lineOrder;
				(*charOrders)[i] = charOrder;
				(*count)++;
				i++;
			}
			charOrder++;
		}
		lineOrder++;
	}
}//찾은 내용을 반환한다. 

/*
* 함수명칭:FindPaper
* 기능:입력한 종이와 일치하는 내용이 있는 위치를 찾는다.
*/
void Paper::FindPaper(Glyph* otherPaper, Long* (*lineOrders), Long* (*charIndexes), Long* count) { //찾을 종이를 입력받는다.
	Long otherPaperLength = otherPaper->GetLength(); //찾을 종이의 길이를 구한다. 
	Glyph* currentLine = 0;
	Long lineOrder = -1;
	Long charIndex = -2;
	Glyph* character = 0;
	Long otherPaperFirstLineLength = -1;
	Long otherPaperLastLineLength = -1;
	
	//종이에서 앞 단어로 찾을 변수
	Long(*lineOrdersOfChar) = 0;
	Long(*charOrders) = 0;
	Long countChar;
	//찾는 종이 변수
	Glyph* clone = 0;
	Long maxLine;
	Long lineLength;
	Long rangeLastLine;
	Long firstLineLastIndex = -2;
	Long lastLineOrder = -1;
	Long i = 0;
	Long j = 0;
	BOOL result = 0;
	
	this->MergeAllDummyLines();
	
	//찾은 개수를 초기화한다.
	*count = 0;
	//검색가능한 최대 줄을 구한다. 
	maxLine = Composite::GetLength() - otherPaperLength;
	//찾는 종이의 마지막 줄의길이를 구한다. 
	lineOrder = otherPaper->Last();
	currentLine = otherPaper->GetAt(lineOrder);
	otherPaperLastLineLength = currentLine->GetLength();
	//찾는 종이의 첫번째 줄의 길이를 구한다.
	currentLine = otherPaper->GetAt(0);
	otherPaperFirstLineLength = currentLine->GetLength();

	//delete[] * lineOrders;
	//delete[] * charIndexes;
	//*lineOrders = NULL;
	//*charIndexes = NULL;

	if (otherPaperFirstLineLength > 0) { //첫번째 줄에 내용이 있으면
		//찾는 종이의 첫번째 글자를 종이에서 찾는다. 
		character = currentLine->GetAt(0);
		this->FindChar(character, &lineOrdersOfChar, &charOrders, &countChar);
		if (countChar > 0) { //찾았으면 찾은 개수만큼 반환 배열을 할당한다. 
			*lineOrders = new Long[countChar];
			//*lineOrders = (Long(*))(calloc((size_t)countChar, (size_t)(sizeof(Long))));
			*charIndexes = new Long[countChar];
			while (i < countChar && lineOrdersOfChar[i] <= maxLine) { //검색된 개수만큼 그리고 검색가능한 최대 줄 까지 반복한다. 
				//검색범위의 마지막 줄의 길이를 확인한다. 
				lineOrder = lineOrdersOfChar[i];
				charIndex = charOrders[i] - 1;
				rangeLastLine = lineOrder + otherPaperLength - 1;
				currentLine = Composite::GetAt(rangeLastLine);
				lineLength = currentLine->GetLength();
				clone = 0;
				if (lineLength >= otherPaperLastLineLength && otherPaperLength <= 1) { //마지막 줄의 길이가 검색 줄의 마지막 줄 길이보다 크커나 같고 한줄만 검색하면 것이면
					//검색범위의 복제본을 만든다. 
					clone = this->Clone(lineOrder, charIndex, lineOrder, charIndex + otherPaperLastLineLength);
				}
				else if (lineLength >= otherPaperLastLineLength && otherPaperLength > 1) { //마지막 줄의 길이가 검색 줄의 마지막 줄 길이보다 크거나 같고 여러줄을 검색하면
					//검색범위의 복제본을 만든다. 
					clone = this->Clone(lineOrder, charIndex, lineOrder + otherPaperLength - 1, otherPaperLastLineLength - 1);
				}
				//검색범위의 복제본이 검색하는 종이와 일치하는지 확인한다. 
				result = 0;
				if (clone != 0) {
					result = clone->IsEqual(otherPaper);
				}
				if (result == 1) { //검색결과가 일치하면 위치와 개수를 기록한다. 
					(*lineOrders)[j] = lineOrder;
					(*charIndexes)[j] = charIndex;
					(*count)++;
					j++;
				}
				//복제본을 지운다. 
				delete clone;
				i++;
			}
		}
	}
	else { //첫번째 줄에 내용이 없으면
		//검색 가능한 줄 수 만큼 할당한다 
		*lineOrders = new Long[maxLine];
		*charIndexes = new Long[maxLine];
		while (i <= maxLine) {//검색 가능한 줄수 만큼 반복한다. 
			lineOrder = i;
			//검색 시작 점을 찾는다. 
			currentLine = Composite::GetAt(lineOrder);
			firstLineLastIndex = currentLine->GetLength() - 1;
			//검색범위의 마지막 줄의 길이를 확인한다. 
			lastLineOrder = lineOrder + otherPaperLength - 1;
			currentLine = Composite::GetAt(lastLineOrder);
			lineLength = currentLine->GetLength();
			clone = 0;
			if (lineLength >= otherPaperLastLineLength) { //마지막 줄의 길이가 검색 줄의 마지막 줄 길이보다 크거나 같으면
				//검색범위의 복제본을 만든다. 
				clone = this->Clone(lineOrder, firstLineLastIndex, lastLineOrder, otherPaperLastLineLength - 1);
			}
			//검색범위의 복제본이 검색하는 종이와 일치하는지 확인한다. 
			result = 0;
			if (clone != 0) {
				result = clone->IsEqual(otherPaper);
			}
			if (result == 1 && j < maxLine) { //검색결과가 일치하면 위치와 개수를 기록한다. 
				(*lineOrders)[j] = lineOrder;
				(*charIndexes)[j] = firstLineLastIndex;
				(*count)++;
				j++;
			}
			//복제본을 지운다. 
			delete clone;
			i++;
		}
	}
	//기존의 검색 부분을 할당해제한다.
	delete[] lineOrdersOfChar;
	delete[] charOrders;
}//찾은 내뇽을 반환한다. 

/*
* 함수명칭:FindPaperUpperLower
* 기능:입력한 종이와 일치하는 내용이 있는 위치를 찾는다.(대소문자 구분없이)
*/
void Paper::FindPaperUpperLower(Glyph* otherPaper, Long* (*lineOrders), Long* (*charIndexes), Long* count) { //찾을 종이를 입력받는다.
	Long otherPaperLength = otherPaper->GetLength(); //찾을 종이의 길이를 구한다. 
	Glyph* currentLine = 0;
	Long lineOrder = -1;
	Long charIndex = -2;
	Glyph* character = 0;
	Long otherPaperFirstLineLength = -1;
	Long otherPaperLastLineLength = -1;

	//종이에서 앞 단어로 찾을 변수
	Long(*lineOrdersOfChar) = 0;
	Long(*charOrders) = 0;
	Long countChar;
	//찾는 종이 변수
	Glyph* clone = 0;
	Long maxLine;
	Long lineLength;
	Long rangeLastLine;
	Long firstLineLastIndex = -2;
	Long lastLineOrder = -1;
	Long i = 0;
	Long j = 0;
	BOOL result = 0;

	this->MergeAllDummyLines();

	//찾은 개수를 초기화한다.
	*count = 0;
	//검색가능한 최대 줄을 구한다. 
	maxLine = Composite::GetLength() - otherPaperLength;
	//찾는 종이의 마지막 줄의길이를 구한다. 
	lineOrder = otherPaper->Last();
	currentLine = otherPaper->GetAt(lineOrder);
	otherPaperLastLineLength = currentLine->GetLength();
	//찾는 종이의 첫번째 줄의 길이를 구한다.
	currentLine = otherPaper->GetAt(0);
	otherPaperFirstLineLength = currentLine->GetLength();

	//delete* lineOrders;
	//delete* charIndexes;

	if (otherPaperFirstLineLength > 0) { //첫번째 줄에 내용이 있으면
		//찾는 종이의 첫번째 글자를 종이에서 찾는다. 
		character = currentLine->GetAt(0);
		this->FindCharUpperLower(character, &lineOrdersOfChar, &charOrders, &countChar);
		if (countChar > 0) { //찾았으면 찾은 개수만큼 반환 배열을 할당한다. 
			*lineOrders = new Long[countChar];
			*charIndexes = new Long[countChar];
			while (i < countChar && lineOrdersOfChar[i] <= maxLine) { //검색된 개수만큼 그리고 검색가능한 최대 줄 까지 반복한다. 
				//검색범위의 마지막 줄의 길이를 확인한다. 
				lineOrder = lineOrdersOfChar[i];
				charIndex = charOrders[i] - 1;
				rangeLastLine = lineOrder + otherPaperLength - 1;
				currentLine = Composite::GetAt(rangeLastLine);
				lineLength = currentLine->GetLength();
				clone = 0;
				if (lineLength >= otherPaperLastLineLength && otherPaperLength <= 1) { //마지막 줄의 길이가 검색 줄의 마지막 줄 길이보다 크커나 같고 한줄만 검색하면 것이면
					//검색범위의 복제본을 만든다. 
					clone = this->Clone(lineOrder, charIndex, lineOrder, charIndex + otherPaperLastLineLength);
				}
				else if (lineLength >= otherPaperLastLineLength && otherPaperLength > 1) { //마지막 줄의 길이가 검색 줄의 마지막 줄 길이보다 크거나 같고 여러줄을 검색하면
					//검색범위의 복제본을 만든다. 
					clone = this->Clone(lineOrder, charIndex, lineOrder + otherPaperLength - 1, otherPaperLastLineLength - 1);
				}
				//검색범위의 복제본이 검색하는 종이와 일치하는지 확인한다. 
				result = 0;
				if (clone != 0) {
					result = clone->IsEqualUpperLower(otherPaper);
				}
				if (result == 1) { //검색결과가 일치하면 위치와 개수를 기록한다. 
					(*lineOrders)[j] = lineOrder;
					(*charIndexes)[j] = charIndex;
					(*count)++;
					j++;
				}
				//복제본을 지운다. 
				delete clone;
				i++;
			}
		}
	}
	else { //첫번째 줄에 내용이 없으면
		//검색 가능한 줄 수 만큼 할당한다 
		*lineOrders = new Long[maxLine];
		*charIndexes = new Long[maxLine];
		while (i <= maxLine) {//검색 가능한 줄수 만큼 반복한다. 
			lineOrder = i;
			//검색 시작 점을 찾는다. 
			currentLine = Composite::GetAt(lineOrder);
			firstLineLastIndex = currentLine->GetLength() - 1;
			//검색범위의 마지막 줄의 길이를 확인한다. 
			lastLineOrder = lineOrder + otherPaperLength - 1;
			currentLine = Composite::GetAt(lastLineOrder);
			lineLength = currentLine->GetLength();
			clone = 0;
			if (lineLength >= otherPaperLastLineLength) { //마지막 줄의 길이가 검색 줄의 마지막 줄 길이보다 크거나 같으면
				//검색범위의 복제본을 만든다. 
				clone = this->Clone(lineOrder, firstLineLastIndex, lastLineOrder, otherPaperLastLineLength - 1);
			}
			//검색범위의 복제본이 검색하는 종이와 일치하는지 확인한다. 
			result = 0;
			if (clone != 0) {
				result = clone->IsEqualUpperLower(otherPaper);
			}
			if (result == 1 && j < maxLine) { //검색결과가 일치하면 위치와 개수를 기록한다. 
				(*lineOrders)[j] = lineOrder;
				(*charIndexes)[j] = firstLineLastIndex;
				(*count)++;
				j++;
			}
			//복제본을 지운다. 
			delete clone;
			i++;
		}
	}
	//기존의 검색 부분을 할당해제한다.
	delete[] lineOrdersOfChar;
	delete[] charOrders;
}//찾은 내뇽을 반환한다. 

/*
* 함수명칭:Clone
* 기능:프로토타입 글자형으로 복제한다
*/
Glyph* Paper::Clone() {
	return new Paper(*this);
}
Glyph* Paper::Clone(Long startLineOrder, Long startCharIndex, Long endLineOrder, Long endCharIndex) { //복제할 범위를 입력받는다.
	GlyphCreater glyphCreater;
	Glyph* clonePaper = 0;
	Glyph* line = 0;
	Glyph* currentLine = 0;
	Long lineOrder = -2;
	Long length = -1;
	//종이를 만들어 빈줄을 넣는다. 
	clonePaper = glyphCreater.Create("");
	line = glyphCreater.Create("\r\n");
	clonePaper->Add(line);
	//시작 줄을 가져온다. 
	currentLine = Composite::GetAt(startLineOrder);
	//시작 줄을 첫 줄에 병합한다.(더미줄이 맨 앞줄이 되는 경우를 방지)
	line->Add(currentLine, 0);
	//남은 줄을 종이에 넣는다. 
	lineOrder = startLineOrder + 1;
	while (lineOrder <= endLineOrder) {
		currentLine = Composite::GetAt(lineOrder);
		clonePaper->Add(currentLine->Clone());
		lineOrder++;
	}
	//마지막 줄에서 범위에 속하지 않는 부분을 제거한다. 
	lineOrder = clonePaper->Last();
	currentLine = clonePaper->GetAt(lineOrder);
	length = currentLine->GetLength();
	currentLine->Remove(endCharIndex + 1, length - 1);
	//첫 줄에서 범위에 속하지 않는 부분을 제거한다. 
	lineOrder = clonePaper->First();
	currentLine = clonePaper->GetAt(lineOrder);
	currentLine->Remove(0, startCharIndex);

	return clonePaper; //만든 종이의 복제본을 반환한다. 
}

/*
* 함수명칭:First
* 기능:처음위치로 이동한다.
*/
Long Paper::First() {
	Long ret;
	Composite::First();
	ret = Composite::Next();
	return ret;
}

/*
* 함수명칭:Previous
* 기능:다음위치로 이동한다.
*/
Long Paper::Previous() {
	Long ret = -2;
	ret = Composite::Previous();
	if (ret < 0) {
		ret = Composite::Next();
	}
	return ret;
}

/*
* 함수명칭:SplitDummyLine
* 기능:더미줄로 나누다의 가상함수
*/
Long Paper::SplitDummyLine(Long lineOrder, Long characterIndex) {//줄의 순서와 줄에서 자를 위치를 입력받는다. 
	GlyphCreater glyphCreater;
	Glyph* line = 0;
	Glyph* dummyLine = 0;
	Glyph* character = 0;
	Glyph* clone = 0;
	Long dummyLineOrder = -1;
	Long order = characterIndex;
	Long length = -1;
	Long i = 0;

	//종이에서 순서의 줄을 가져온다. 
	line = this->GetAt(lineOrder);
	//새 더미줄을 만든다. 
	dummyLine = glyphCreater.Create("\r");
	length = line->GetLength();
	while (i < length - order - 1) {//위치 이전의 순서에서 줄의 끝까지 반복한다. 
		//위치 다음의 단어를 가져온다. 
		character = line->GetAt(order + 1);
		//단어의 클론을 만든다. 
		clone = character->Clone();
		//클론을 새 더미줄에 넣는다. 
		dummyLine->Add(clone);
		//줄에서 위치 다음의 단어를 제거한다. 
		line->Remove(order + 1);
		i++;
	}
	//새 더미줄을 줄 다음의 위치에 넣는다. 
	dummyLineOrder = Composite::Add(lineOrder + 1, dummyLine);
	//새 더매줄의 위치를 반환한다.
	return dummyLineOrder;
}

/*
* 함수명칭:MergeAllDummyLines
* 기능:모든 더미줄을 기존줄에 다 합친다.
*/
void Paper::MergeAllDummyLines() {
	Glyph* lineRet = 0;
	Glyph* currentLine = 0;
	Glyph* character = 0;
	Glyph* clone = 0;
	Long lineOrder = -1;
	Long paperLength = -1;
	Long i = 0;
	Long j;

	//종이의 길이를 구한다.
	paperLength = this->GetLength();
	//종이에서 처음줄로 이동한다.
	lineOrder = this->First();
	lineRet = this->GetAt(lineOrder);
	//반환된 줄을 현재줄로 지정한다.
	currentLine = lineRet;
	//줄의 마지막으로 이동한다. 
	currentLine->Last();
	while (i < paperLength) {//줄이 마지막줄일때까지 반복한다.
		if (dynamic_cast<DummyLine*>(lineRet)) {
			//줄이 더미줄이면 현재 줄과 병합한다.
			j = 0;
			while (j < lineRet->GetLength()) {
				character = lineRet->GetAt(j);
				clone = character->Clone();
				currentLine->Add(clone);
				j++;
			}
			Composite::Remove(lineOrder);
		}
		else if(dynamic_cast<Line*>(lineRet)){
			//줄이 더미줄이 아니면 현재 줄로 지정한다. 
			currentLine = lineRet;
			currentLine->Last();
		}
		//종이에서 다음줄로 이동한다. 
		lineOrder = this->Next();
		lineRet = GetAt(lineOrder);
		i++;
	}
}

/*
* 함수명칭:MergeDummyLines
* 기능:더미줄을 기존줄에 합치는 함수의 가상함수
*/
Long Paper::MergeDummyLines(Long startlineOrder) {
	Glyph* startLine = 0;
	Glyph* currentLine = 0;
	Glyph* character = 0;
	Glyph* clone = 0;
	Long lineOrder = -1;
	Long previousLineOrder = -2;
	Long charIndex = -1;
	Long previousCharOrder;
	Long countRepeat = 0;
	Long i = 0;

	//종이에서 시작줄의 위치로 이동한다.
	startlineOrder = this->Move(startlineOrder);
	//시작줄을 가져온다. 
	startLine = this->GetAt(startlineOrder);
	//시작줄에서 끝으로 이동한다.
	startLine->Last();
	//다음줄을 가져온다. 
	previousLineOrder = startlineOrder;
	lineOrder = this->Next();
	currentLine = this->GetAt(lineOrder);
	
	while (lineOrder != previousLineOrder && dynamic_cast<DummyLine*>(currentLine)) {
		previousCharOrder = -1;
		currentLine->First();
		charIndex = currentLine->Next();
		while (charIndex != previousCharOrder) {
			//현재 순서의 단어를 가져온다. 
			character = currentLine->GetAt(charIndex);
			//단어의 복사본을 시작 줄에 넣는다. 
			clone = character->Clone();
			startLine->Add(clone);
			//다음 단어위치순서로 이동한다.
			previousCharOrder = charIndex;
			charIndex = currentLine->Next();
		}
		//다음줄을 가져온다. 
		previousLineOrder = lineOrder;
		lineOrder = this->Next();
		currentLine = this->GetAt(lineOrder);
		//더미줄수를 센다
		countRepeat++;
	}
	while (i < countRepeat) { //더비줄수만큼 반복한다. 
		Composite::Remove(startlineOrder + 1);
		i++;
	}
	//종이에서 시작줄의 위치로 이동한다.
	startlineOrder = this->Move(startlineOrder);
	//시작줄의 위치를 반환한다. 
	return startlineOrder;
}

/*
* 함수명칭:GetLocation
* 기능:절대 위치를 구한다.
*/
void Paper::GetLocation(Long lineOrder, Long charIndex, Long* lineLocation, Long* charLocation) { //줄의 순서와 위치를 입력받는다
	Glyph* currentLine = 0;
	Glyph* lineToFind = 0;
	Long lineLength; //줄의 길이
	Long lineIndexNumber; //줄의 위치 갯수
	Long lineCount = 0;
	
	*charLocation = charIndex;
	lineOrder = this->Move(lineOrder);
	currentLine = this->GetAt(lineOrder);
	while (dynamic_cast<DummyLine*>(currentLine)) { //줄이 더미줄이 아닐 때 까지 반복한다.
		//이전 줄로 이동한다. 
		lineOrder = this->Previous();
		currentLine = this->GetAt(lineOrder);
		//총 위치값을 갱신한다.
		lineLength = currentLine->GetLength();
		lineIndexNumber = lineLength;
		*charLocation = *charLocation + lineIndexNumber;
	}
	//종이에서 찾은 줄의 순서(더비줄을 뺀 순서)를 구한다.
	lineToFind = currentLine;
	lineOrder = this->First();
	currentLine = this->GetAt(lineOrder);
	lineCount = 1;
	while (currentLine != lineToFind) {
		lineOrder = this->Next();
		currentLine = this->GetAt(lineOrder);
		if (!dynamic_cast<DummyLine*>(currentLine)) {
			lineCount++;
		}
	}
	*lineLocation = lineCount - 1; //순서를 구한다.
}//줄의 순서와 총 위치를 반환한다.

/*
* 함수명칭:MoveToLocation
* 기능:절대 위치로 이동한다.
*/
void Paper::MoveToLocation(Long lineLocation, Long charLocation, Long* lineOrder, Long* charIndex) { //줄의 위치와 총 위치를 입력받는다.
	Glyph* currentLine = 0;
	Long lineCount = 1;
	Long lineLength;
	Long i = 1;

	//종이에서 줄의 위치의 줄을 가져온다. 
	*lineOrder = this->First();
	currentLine = this->GetAt(*lineOrder);
	while (i < this->GetLength() && lineCount < lineLocation + 1) {
		*lineOrder = this->Next();
		currentLine = this->GetAt(*lineOrder);
		if (!dynamic_cast<DummyLine*>(currentLine)) {
			lineCount++;
		}
		i++;
	}
	*charIndex = charLocation;
	if (currentLine != 0) {
		lineLength = currentLine->GetLength();
		while (*charIndex > lineLength - 1) {//줄의 길이가 총 위치보다 작은 동안 반복한다.
			//총 위치를 갱신한다.
			*charIndex = *charIndex - lineLength;
			//다음줄로 이동한다.
			*lineOrder = this->Next();
			currentLine = this->GetAt(*lineOrder);
			lineLength = currentLine->GetLength();
		}
		//줄에서 갱신된 위치로 이동한다.
		currentLine->Move(*charIndex);
	}
} //현재 줄의 위치와 갱신된 총 위치를 반환한다.

/*
* 함수명칭:GetString
* 기능:줄의 문자를 가져온다.
*/
string Paper::GetString() {
	Glyph* glyph = 0;
	string ret = "";
	string addRear;
	Long i = 0;
	Long length;
	length = this->GetLength();

	if (length > 0) {
		glyph = this->GetAt(i);
		addRear = glyph->GetString();
		ret = ret + addRear;
		i++;
	}
	while (i < length) {
		glyph = this->GetAt(i);
		addRear = glyph->GetString();
		ret = ret + "\r\n" + addRear; //\r\n
		i++;
	}
	return ret;
}

/*
* 함수명칭:GetExactString
* 기능:저장을 위해 자료구조에 저장된 정확한 아스키코드의 문자를 문자열에 저장하여 출력한다.
*/
string Paper::GetExactString() {
	Glyph* glyph = 0;
	string ret = "";
	string addRear;
	Long i = 0;
	Long length;
	length = this->GetLength();

	if (length > 0) {
		glyph = this->GetAt(i);
		addRear = glyph->GetExactString();
		ret = ret + addRear;
		i++;
	}
	while (i < length) {
		glyph = this->GetAt(i);
		addRear = glyph->GetExactString();
		ret = ret + "\r\n" + addRear; //\r\n
		i++;
	}
	return ret;
}

/*
* 함수명칭:Accept
* 기능:Element로서 Visitor의 Visit를 허용한다.
*/
void Paper::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

/*
* 함수명칭:IsEqual
* 기능:입력값이 같은지 비교한다
*/
BOOL Paper::IsEqual(Long previousLineOrder, Long previousCharIndex) {
	BOOL ret = 0;
	Glyph* currentLine = 0;
	Long lineOrder = -1;
	Long charIndex = -2;

	lineOrder = this->GetCurrent();
	currentLine = this->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	if (lineOrder == previousLineOrder && charIndex == previousCharIndex) {
		ret = 1;
	}

	return ret;
}
BOOL Paper::IsEqual(Glyph* otherPaper) {
	BOOL ret = 0;
	Long paperLength = Composite::GetLength();
	Long otherPaperLength = otherPaper->GetLength();
	Long lineLength;
	Long otherLineLength;
	Glyph* currentLine = 0;
	Glyph* otherLine = 0;
	Long lineOrder = -1;
	Long charIndex = -2;
	Glyph* character = 0;
	Glyph* otherCharacter = 0;
	int flag = 0;
	Long i = 0;
	Long j;
	BOOL result = 0;

	if (paperLength != otherPaperLength) {
		flag = 1;
	}
	while (i < paperLength && flag == 0) {
		currentLine = Composite::GetAt(i);
		otherLine = otherPaper->GetAt(i);
		lineLength = currentLine->GetLength();
		otherLineLength = otherLine->GetLength();
		if (lineLength != otherLineLength) {
			flag = 1;
		}
		j = 0;
		while (j < lineLength && flag == 0) {
			character = currentLine->GetAt(j);
			otherCharacter = otherLine->GetAt(j);
			result = character->IsEqual(otherCharacter);
			if (result == 0) {
				flag = 1;
			}
			j++;
		}
		i++;
	}
	if (flag == 0) {
		ret = 1;
	}
	return ret;
}

/*
* 함수명칭:IsEqualUpperLower
* 기능:대소문자 구분 안하고 같은지 찾는다. 
*/
BOOL Paper::IsEqualUpperLower(Glyph* otherPaper) {
	BOOL ret = 0;
	Long paperLength = Composite::GetLength();
	Long otherPaperLength = otherPaper->GetLength();
	Long lineLength;
	Long otherLineLength;
	Glyph* currentLine = 0;
	Glyph* otherLine = 0;
	Long lineOrder = -1;
	Long charIndex = -2;
	Glyph* character = 0;
	Glyph* otherCharacter = 0;
	int flag = 0;
	Long i = 0;
	Long j;
	BOOL result = 0;

	if (paperLength != otherPaperLength) {
		flag = 1;
	}
	while (i < paperLength && flag == 0) {
		currentLine = Composite::GetAt(i);
		otherLine = otherPaper->GetAt(i);
		lineLength = currentLine->GetLength();
		otherLineLength = otherLine->GetLength();
		if (lineLength != otherLineLength) {
			flag = 1;
		}
		j = 0;
		while (j < lineLength && flag == 0) {
			character = currentLine->GetAt(j);
			otherCharacter = otherLine->GetAt(j);
			result = character->IsEqualUpperLower(otherCharacter);
			if (result == 0) {
				flag = 1;
			}
			j++;
		}
		i++;
	}
	if (flag == 0) {
		ret = 1;
	}
	return ret;
}

/*
* 함수명칭:IsNotEqual
* 기능:입력값이 다른지 비교한다
*/
BOOL Paper::IsNotEqual(Long previousLineOrder, Long previousCharIndex) {
	BOOL ret = 0;
	Glyph* currentLine = 0;
	Long lineOrder = -1;
	Long charIndex = -2;

	lineOrder = this->GetCurrent();
	currentLine = this->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	if (lineOrder != previousLineOrder || charIndex != previousCharIndex) {
		ret = 1;
	}

	return ret;
}

/*
* 함수명칭:GetCharNumber
* 기능:종이 내의 글자수를 계산하여 반환한다.
*/
Long Paper::GetCharNumber() {
	Long charNumber = 0;
	Long i = 0;
	Glyph* currentLine = 0;
	Long lineLength = -1;
	Long paperLength = Composite::GetLength();
	while (i < paperLength) {
		currentLine = Composite::GetAt(i);
		lineLength = currentLine->GetLength();
		charNumber = charNumber + lineLength;
		i++;
	}
	return charNumber;
}

/*
* 함수명칭:operator=
* 기능:치환연산자
*/
Paper& Paper::operator=(const Paper& source) {
	Composite::operator=(source);
	return *this;
}

/*
* 함수명칭:operator[]
* 기능:첨자연산자
*/
Glyph* Paper::operator[](Long order) {
	return this->GetAt(order);
}

#include<iostream>
using namespace std;
int main(int argc, char* argv[]) {
	GlyphCreater glyphCreater;
	Glyph* paper = 0;
	Glyph* line = 0;
	Glyph* lineReturn = 0;
	Glyph* nextLine = 0;
	Glyph* tempLine = 0;
	Glyph* character = 0;
	Glyph* characterReturn = 0;

	int indexLine = -1;
	int indexCharacter = -1;

	//기본 테스트용 문자
	paper = glyphCreater.Create("");
	line = glyphCreater.Create("\r\n");
	indexLine = paper->Add(line);
	lineReturn = paper->GetAt(indexLine);
	character = glyphCreater.Create("가");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());
	character = glyphCreater.Create("나");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());
	character = glyphCreater.Create("다");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());
	character = glyphCreater.Create(" ");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());
	character = glyphCreater.Create("1");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());
	character = glyphCreater.Create("2");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());
	character = glyphCreater.Create("3");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());
	character = glyphCreater.Create(" ");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());
	character = glyphCreater.Create(" ");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());

	line = glyphCreater.Create("\r\n");
	indexLine = paper->Add(line);
	lineReturn = paper->GetAt(indexLine);
	cout << endl;

	character = glyphCreater.Create(" ");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());

	character = glyphCreater.Create("A");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());

	character = glyphCreater.Create("B");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());

	character = glyphCreater.Create("C");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());

	line = glyphCreater.Create("\r\n");
	indexLine = paper->Add(line);
	lineReturn = paper->GetAt(indexLine);
	cout << endl;

	character = glyphCreater.Create("a");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());
	cout << endl;

	//cout << endl << static_cast<string>(paper->GetString()) << endl;

#if 0 //이동 테스트 코드
	cout << endl << "줄 이동" << endl;
	cout << endl << "First" << endl;
	current = paper->First();
	//!!!!!!!!!!! 맨 처음이 줄은 0이지 않을까???
	cout << current << "\t";
	current = paper->GetCurrent();
	cout << current << "\t" << endl;
	lineReturn = paper->GetAt(current);
	cout << static_cast<string>(lineReturn->GetString()) << endl;
	cout << endl << "Next" << endl;
	current = paper->Next();
	cout << current << "\t" << endl;
	lineReturn = paper->GetAt(current);
	cout << static_cast<string>(lineReturn->GetString()) << endl;
	cout << endl << "Last" << endl;
	current = paper->Last();
	cout << current << "\t" << endl;
	lineReturn = paper->GetAt(current);
	cout << static_cast<string>(lineReturn->GetString()) << endl;
	cout << endl << "Previous" << endl;
	current = paper->Previous();
	cout << current << "\t" << endl;
	lineReturn = paper->GetAt(current);
	cout << static_cast<string>(lineReturn->GetString()) << endl;

	cout << endl << "Move" << endl;
	current = paper->Move(0);
	cout << current << "\t" << endl;
	lineReturn = paper->GetAt(current);
	cout << static_cast<string>(lineReturn->GetString()) << endl;

	//글자 이동
	cout << endl << "글자 이동" << endl;
	cout << endl << "First" << endl;
	current = lineReturn->First();
	cout << current << "\t";
	current = lineReturn->GetCurrent();
	cout << current << "\t" << endl;
	cout << endl << "Next" << endl;
	current = lineReturn->Next();
	cout << current << "\t" << endl;
	cout << endl << "Last" << endl;
	current = lineReturn->Last();
	cout << current << "\t" << endl;
	cout << endl << "Previous" << endl;
	current = lineReturn->Previous();
	cout << current << "\t" << endl;
	cout << endl << "Move" << endl;
	current = lineReturn->Move(8);
	cout << current << "\t" << endl;

	cout << endl << "이전 글자로 이동" << endl;
	current = lineReturn->PreviousWord();
	cout << current << "\t" << endl;
	current = lineReturn->PreviousWord();
	cout << current << "\t" << endl;
	current = lineReturn->PreviousWord();
	cout << current << "\t" << endl;
	lineReturn->Move(7);
	current = lineReturn->PreviousWord();
	cout << current << "\t" << endl;
	lineReturn->Move(6);
	current = lineReturn->PreviousWord();
	cout << current << "\t" << endl;
	lineReturn->Move(5);
	current = lineReturn->PreviousWord();
	cout << current << "\t" << endl;

	cout << endl << "다음 글자로 이동" << endl;
	lineReturn->Move(8);
	current = lineReturn->NextWord();
	cout << current << "\t" << endl;
	lineReturn->Move(7);
	current = lineReturn->NextWord();
	cout << current << "\t" << endl;
	lineReturn->Move(6);
	current = lineReturn->NextWord();
	cout << current << "\t" << endl;
	lineReturn->Move(5);
	current = lineReturn->NextWord();
	cout << current << "\t" << endl;
	lineReturn->Move(1);
	current = lineReturn->NextWord();
	cout << current << "\t" << endl;
	current = lineReturn->NextWord();
	cout << current << "\t" << endl;
	current = lineReturn->NextWord(); //중복 명령 테스트
	cout << current << "\t" << endl;
	lineReturn->Move(-1);
	current = lineReturn->NextWord();
	cout << current << "\t" << endl;
	current = lineReturn->NextWord();
	cout << current << "\t" << endl;

	lineReturn = paper->GetAt(1);
	lineReturn->Move(-1);
	current = lineReturn->NextWord();
	cout << current << "\t" << endl;
#endif //이동 테스트 코드

#if 0 // 끼워쓰기 테스트 코드
	line = glyphCreater.Create("\r\n");
	indexLine = paper->Add(1, line);
	lineReturn = paper->GetAt(indexLine);
	cout << endl << static_cast<string>(paper->GetString()) << endl;
	cout << paper->GetCurrent() << "\t" << lineReturn->GetCurrent() << endl << endl;

	indexLine = paper->Move(2);
	lineReturn = paper->GetAt(indexLine);
	cout << indexLine << "\t";
	current = lineReturn->Move(1);
	cout << current << endl;
	character = glyphCreater.Create("라");
	indexCharacter = lineReturn->Add(character);
	cout << endl << static_cast<string>(paper->GetString()) << endl;
	cout << paper->GetCurrent() << "\t" << lineReturn->GetCurrent() << endl << endl;

	indexLine = paper->Move(0);
	lineReturn = paper->GetAt(indexLine);
	cout << indexLine << endl;
	character = glyphCreater.Create("F");
	indexCharacter = lineReturn->Add(8, character);
	cout << endl << static_cast<string>(paper->GetString()) << endl;
	cout << paper->GetCurrent() << "\t" << lineReturn->GetCurrent() << endl << endl;

	indexLine = paper->Move(2);
	line = glyphCreater.Create("\r\n");
	indexLine = paper->Add(line);
	lineReturn = paper->GetAt(indexLine);
	cout << endl << static_cast<string>(paper->GetString()) << endl;
	cout << paper->GetCurrent() << "\t" << lineReturn->GetCurrent() << endl << endl;
#endif // 끼워쓰기 테스트 코드

#if 0 //지우기 테스트 코드
	indexLine = paper->Move(0);
	lineReturn = paper->GetAt(indexLine);
	lineReturn->Remove(2);
	cout << endl << static_cast<string>(paper->GetString()) << endl;
	cout << paper->GetCurrent() << "\t" << lineReturn->GetCurrent() << endl << endl;

	indexLine = paper->Move(2);
	lineReturn = paper->GetAt(indexLine);
	lineReturn->Remove(0);
	cout << endl << static_cast<string>(paper->GetString()) << endl;
	cout << paper->GetCurrent() << "\t" << lineReturn->GetCurrent() << endl << endl;

	paper->Remove(1);
	cout << endl << static_cast<string>(paper->GetString()) << endl;
	indexLine = paper->GetCurrent();
	lineReturn = paper->GetAt(indexLine);
	cout << paper->GetCurrent() << "\t" << lineReturn->GetCurrent() << endl << endl;

	paper->Remove(1);
	cout << endl << static_cast<string>(paper->GetString()) << endl;
	indexLine = paper->GetCurrent();
	lineReturn = paper->GetAt(indexLine);
	cout << paper->GetCurrent() << "\t" << lineReturn->GetCurrent() << endl << endl;

	indexLine = paper->GetCurrent();
	lineReturn = paper->GetAt(indexLine);
	while (lineReturn->GetLength() > 0) {
		lineReturn->Remove(0);
		cout << endl << static_cast<string>(paper->GetString()) << endl;
		cout << paper->GetCurrent() << "\t" << lineReturn->GetCurrent() << "\t" << lineReturn->GetLength() << endl;
	}
#endif //지우기 테스트 코드

#if 0//줄 나누기 줄 합치기 테스트
	cout << endl << "줄 합치기" << endl;
	//줄 합치기
	indexLine = paper->Move(0);
	lineReturn = paper->GetAt(indexLine);
	nextLine = paper->GetAt(1);
	//첫번째 줄 쥐의 두번째 줄을 붙인다
	current = lineReturn->AppendLineFromRear(nextLine);
	cout << current;
	cout << endl << static_cast<string>(paper->GetString()) << endl;
	
	//두번째 줄을 지운다. 
	paper->Remove(1);
	cout << endl << static_cast<string>(paper->GetString()) << endl;

	//줄 나누기
	cout << endl << "줄 나누기" << endl;
	//첫번째 줄을 4번째 위치를 기준으로 나눈다. 
	tempLine = lineReturn->SplitLineRearAsLine(3);
	paper->Add(1, tempLine);
	cout << endl << static_cast<string>(paper->GetString()) << endl;
#endif

#if 0 //더미라인 테스트
	cout << endl << "더미 라인 테스트" << endl;
	cout << "더미 라인 분리" << endl;
	indexLine = paper->SplitDummyLine(0, 2);
	cout << indexLine;
	cout << endl << static_cast<string>(paper->GetString()) << endl;
	cout << endl;

	indexLine = paper->SplitDummyLine(1, 2);
	cout << indexLine;
	cout << endl << static_cast<string>(paper->GetString()) << endl;
	cout << endl;

	indexLine = paper->SplitDummyLine(3, 1);
	cout << indexLine;
	cout << endl << static_cast<string>(paper->GetString()) << endl;
	cout << endl;

	cout << "더미 라인 병합" << endl;
	//단일 줄 병함
	paper->MergeDummyLines(3);
	cout << endl << static_cast<string>(paper->GetString()) << endl;

	//전체 줄 병합
	//paper->MergeAllDummyLines();
	//cout << endl << static_cast<string>(paper->GetString()) << endl;
#endif//더미라인 테스트

#if 0 //절대 위치 테스트
	//더미라인 테스를 합친 절대 위치 테스트
	Long lineLocation = -99; //줄의 절대 순서(더미줄을 제외한 순서)
	Long charLocation = -99; //절대 위치(더비줄을 제외한 글자의 순서)
	Long lineOrder = -1;
	Long charIndex = -2;

	cout << endl << "절대 위치 테스트" << endl;
	//맨앞으로 이동 후 절대 위치를 기억한다.
	cout << "맨 앞 으로 이동" << endl;
	lineOrder = 0;
	charIndex = -1;
	paper->Move(lineOrder);
	paper->GetAt(lineOrder)->Move(charIndex);
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "GetLocation 함수 전:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	paper->GetLocation(lineOrder, charIndex, &lineLocation, &charLocation);
	cout << "GetLocation 함수 후:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	
	cout << "라인 분리" << endl;
	indexLine = paper->SplitDummyLine(0, 2);
	cout << static_cast<string>(paper->GetString()) << endl;
	
	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "절대 위치로 이동" << endl;
	paper->MoveToLocation(lineLocation, charLocation, &lineOrder, &charIndex);
	cout << "MoveToLocation 함수 후:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << endl;



	//맨 뒤로 이동 후 절대 위치를 기억한다.
	cout << "맨 뒤로 이동" << endl;
	//lineOrder = 0;
	//charIndex = -1;
	lineOrder = paper->Last();
	charIndex = paper->GetAt(lineOrder)->Last();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "GetLocation 함수 전:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	paper->GetLocation(lineOrder, charIndex, &lineLocation, &charLocation);
	cout << "GetLocation 함수 후:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;

	cout << "라인 분리" << endl;
	indexLine = paper->SplitDummyLine(1, 2);
	cout << static_cast<string>(paper->GetString()) << endl;

	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;

	cout << "절대 위치로 이동" << endl;
	paper->MoveToLocation(lineLocation, charLocation, &lineOrder, &charIndex);
	cout << "MoveToLocation 함수 후:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << endl;



	//4번째 줄 2번째 위치로 이동후 절대 위치를 기억한다.
	cout << "4번째 줄 2번째 위치로 이동" << endl;
	lineOrder = 3;
	charIndex = 1;
	paper->Move(lineOrder);
	paper->GetAt(lineOrder)->Move(charIndex);
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "GetLocation 함수 전:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	paper->GetLocation(lineOrder, charIndex, &lineLocation, &charLocation);
	cout << "GetLocation 함수 후:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;

	cout << "라인 분리" << endl;
	indexLine = paper->SplitDummyLine(3, 1);
	cout << static_cast<string>(paper->GetString()) << endl;

	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "절대 위치로 이동" << endl;
	paper->MoveToLocation(lineLocation, charLocation, &lineOrder, &charIndex);
	cout << "MoveToLocation 함수 후:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << endl;


	
	//5번째 줄의 끝으로 이동 후 절대 위치를 기억한다.
	cout << "5번째 줄의 끝으로 이동 후 절대 위치를 기억한다." << endl;
	lineOrder = 4;
	charIndex = 1;
	paper->Move(lineOrder);
	paper->GetAt(lineOrder)->Move(charIndex);
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "GetLocation 함수 전:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	paper->GetLocation(lineOrder, charIndex, &lineLocation, &charLocation);
	cout << "GetLocation 함수 후:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;

	cout << "라인 병합" << endl;
	paper->MergeAllDummyLines();
	cout << static_cast<string>(paper->GetString()) << endl;

	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "절대 위치로 이동" << endl;
	paper->MoveToLocation(lineLocation, charLocation, &lineOrder, &charIndex);
	cout << "MoveToLocation 함수 후:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << endl;

	//첫번째 줄의 5번째 위치로 이동 후 절대 위치를 기억한다.
	cout << "첫번째 줄의 5번째 위치로 이동 후 절대 위치를 기억한다." << endl;
	lineOrder = 0;
	charIndex = 4;
	paper->Move(lineOrder);
	paper->GetAt(lineOrder)->Move(charIndex);
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "GetLocation 함수 전:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	paper->GetLocation(lineOrder, charIndex, &lineLocation, &charLocation);
	cout << "GetLocation 함수 후:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;

	indexLine = paper->SplitDummyLine(0, 2);
	cout << static_cast<string>(paper->GetString()) << endl;

	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "절대 위치로 이동" << endl;
	paper->MoveToLocation(lineLocation, charLocation, &lineOrder, &charIndex);
	cout << "MoveToLocation 함수 후:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << endl;



	//세번째 줄의 3번째 위치로 이동 후 절대 위치를 기억한다.
	cout << "세번째 줄의 3번째 위치로 이동 후 절대 위치를 기억한다." << endl;
	lineOrder = 2;
	charIndex = 2;
	paper->Move(lineOrder);
	paper->GetAt(lineOrder)->Move(charIndex);
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "GetLocation 함수 전:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	paper->GetLocation(lineOrder, charIndex, &lineLocation, &charLocation);
	cout << "GetLocation 함수 후:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;

	//전체 줄 병합
	cout << "라인 병합" << endl;
	paper->MergeAllDummyLines();
	cout << static_cast<string>(paper->GetString()) << endl;

	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "절대 위치로 이동" << endl;
	paper->MoveToLocation(lineLocation, charLocation, &lineOrder, &charIndex);
	cout << "MoveToLocation 함수 후:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << endl;
#endif //절대 위치 테스트 

#if 0 //같은 단계 Add Remove 테스트
	cout << endl << "Add 테스트 - Line" << endl;
	//종이를 복사한다.
	Glyph* otherPaper = paper->Clone();
	//2번째 줄의 2번째 위치에 복사본의 첫번째줄을 넣는다.
	Glyph* otherLine = otherPaper->GetAt(0);
	lineReturn = paper->GetAt(1);
	indexCharacter = lineReturn->Add(otherLine, 1);
	cout << "CharIndex : " << indexCharacter << endl;
	cout << lineReturn->GetString() << endl;
	//종이의 2번째 줄에 복사한 종이를 삽입한다.
	cout << endl << "Add 테스트 - Paper" << endl;
	indexLine = paper->Add(otherPaper, 1);
	cout << "LineIndex : " << indexLine << endl;
	cout << paper->GetString() << endl;

	cout << endl << "Remove 테스트 - Paper - 끝 " << endl;
	indexLine = paper->Remove(5, 5);
	cout << "LineIndex : " << indexLine << endl;
	cout << paper->GetString() << endl;

	cout << endl << "Remove 테스트 - Paper - 중간 " << endl;
	indexLine = paper->Remove(1, 2);
	cout << "LineIndex : " << indexLine << endl;
	cout << paper->GetString() << endl;

	cout << endl << "Remove 테스트 - Paper - 맨앞 " << endl;
	indexLine = paper->Remove(0, 1);
	cout << "LineIndex : " << indexLine << endl;
	indexLine = paper->Move(0);
	cout << "LineIndex : " << indexLine << endl;
	cout << paper->GetString() << endl;

	cout << endl << "Remove 테스트 - Line - 중간 " << endl;
	lineReturn = paper->GetAt(0);
	indexCharacter = lineReturn->Remove(2, 6);
	cout << "CharIndex : " << indexCharacter << endl;
	cout << lineReturn->GetString() << endl;

	cout << endl << "Remove 테스트 - Line - 맨뒤 " << endl;
	indexCharacter = lineReturn->Remove(6, 7);
	cout << "CharIndex : " << indexCharacter << endl;
	cout << lineReturn->GetString() << endl;

	cout << endl << "Remove 테스트 - Line - 전부 " << endl;
	indexCharacter = lineReturn->Remove(0, 5);
	cout << "CharIndex : " << indexCharacter << endl;
	cout << lineReturn->GetString() << endl;

	cout << endl << "Remove 테스트 - Line - 전부 나갔는지 확인" << endl;
	character = glyphCreater.Create("가");
	indexCharacter = lineReturn->Add(character);
	cout << lineReturn->GetString() << endl;

#endif //같은 단계 Add Remove 테스트

//#if 0 //Find 테스트
	Glyph* temp = paper->Clone();
	tempLine = glyphCreater.Create("\r\n");
	temp->Add(0, tempLine);

	paper->Add(paper, 3);
	paper->Add(paper, 6);
	cout << endl << static_cast<string>(paper->GetString()) << endl << endl;

	//ABC를 검색
	Glyph* paperToFind = glyphCreater.Create("");
	Glyph* currentLine = glyphCreater.Create("\r\n");
	Long(*lineOrders) = 0;
	Long(*charIndexes) = 0;
	Long count = 0;
	Long i = 0;

	paperToFind->Add(currentLine);
	character = glyphCreater.Create("A");
	currentLine->Add(character);
	character = glyphCreater.Create("b");
	currentLine->Add(character);
	character = glyphCreater.Create("C");
	currentLine->Add(character);
	cout << static_cast<string>(currentLine->GetString()) << endl;
	
	paper->FindPaperUpperLower(paperToFind, &lineOrders, &charIndexes, &count);
	i = 0;
	while (i < count) {
		cout << i + 1 << "번째" << endl;
		cout << "줄:" << lineOrders[i] << "\t" << "시작위치:" << charIndexes[i] << endl << endl;
		i++;
	}
	cout << endl;
	delete[] lineOrders;
	delete[] charIndexes;
	currentLine->Remove(0, 2);
	
	//다 12 를 찾는다. 
	character = glyphCreater.Create("다");
	currentLine->Add(character);
	character = glyphCreater.Create(" ");
	currentLine->Add(character);
	character = glyphCreater.Create("1");
	currentLine->Add(character);
	character = glyphCreater.Create("2");
	currentLine->Add(character);
	cout << static_cast<string>(currentLine->GetString()) << endl;

	paper->FindPaper(paperToFind, &lineOrders, &charIndexes, &count);
	i = 0;
	while (i < count) {
		cout << i + 1 << "번째" << endl;
		cout << "줄:" << lineOrders[i] << "\t" << "시작위치:" << charIndexes[i] << endl << endl;
		i++;
	}
	cout << endl;
	delete[] lineOrders;
	delete[] charIndexes;
	currentLine->Remove(0, 3);

	//엔터
	// A를 찾는다. 
	Glyph* otherLine = glyphCreater.Create("\r\n");
	paperToFind->Add(0, otherLine);

	character = glyphCreater.Create(" ");
	currentLine->Add(character);
	character = glyphCreater.Create("A");
	currentLine->Add(character);
	cout << static_cast<string>(currentLine->GetString()) << endl;

	paper->FindPaper(paperToFind, &lineOrders, &charIndexes, &count);
	i = 0;
	while (i < count) {
		cout << i + 1 << "번째" << endl;
		cout << "줄:" << lineOrders[i] << "\t" << "시작위치:" << charIndexes[i] << endl << endl;
		i++;
	}
	cout << endl;
	delete[] lineOrders;
	delete[] charIndexes;
	currentLine->Remove(0, 1);

	//엔터
	// A를 찾는다. 
	character = glyphCreater.Create("A");
	currentLine->Add(character);
	cout << static_cast<string>(currentLine->GetString()) << endl;

	paper->FindPaperUpperLower(paperToFind, &lineOrders, &charIndexes, &count);
	i = 0;
	while (i < count) {
		cout << i + 1 << "번째" << endl;
		cout << "줄:" << lineOrders[i] << "\t" << "시작위치:" << charIndexes[i] << endl << endl;
		i++;
	}
	cout << endl;
	delete[] lineOrders;
	delete[] charIndexes;
	currentLine->Remove(0, 0);
	paperToFind->Remove(1);

//#endif //Find 테스트

	paper->FindPaper(temp, &lineOrders, &charIndexes, &count);
	i = 0;
	while (i < count) {
		cout << i + 1 << "번째" << endl;
		cout << "줄:" << lineOrders[i] << "\t" << "시작위치:" << charIndexes[i] << endl << endl;
		i++;
	}
	cout << endl;
	delete[] lineOrders;
	delete[] charIndexes;

	return 0;
}
