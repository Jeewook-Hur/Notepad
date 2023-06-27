//Paper.cpp
/*
* ���ϸ�Ī:Paper.cpp
* ���:����
* �ۼ���:������
* �ۼ�����:2022/7/11
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
* �Լ���Ī:Paper
* ���:������
*/
Paper::Paper(Long capacity) :Composite(capacity) {
}
Paper::Paper(const Paper& source) : Composite(source) {
}

/*
* �Լ���Ī:~Paper
* ���:�Ҹ���
*/
Paper::~Paper() {
}

/*
* �Լ���Ī:Add
* ���:�Է��� ��ġ�� �Է��� ���̸� ���Ѵ�.
*/
Long Paper::Add(Glyph* paperToAdd, Long lineOrder, Long charIndex) { //�Է��� ����, �Է��� ��ġ�� �Է¹޴´�. 
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

	//���� ���̿� �Է��� ���̸� �Է��� ��ġ ������ ���� �Է��Ѵ�. 
	Composite::Add(paperToAdd, lineOrder + 1);

	//���� ������ ���̸� ���Ѵ�.
	paperLength = paperToAdd->GetLength();
	//���� ���̰� �� ������ �������� ������ ���� ���Ѵ�. 
	endLineOrder = lineOrder + paperLength;
	
	//�Է��� ��ġ�� ���� �����´�. 
	currentLine = Composite::GetAt(lineOrder);
	//���� ���� ���̸� �����´�. 
	currentLineLength = currentLine->GetLength();

	if (charIndex < currentLineLength - 1) {//���� ���� �Է� ��ġ�� �ǵڰ� �ƴϸ�
		//���� Ŭ���� �����.
		clone = currentLine->Clone();
		//���� ���� ���� ��ġ���� ������ �����Ѵ�.
		currentLine->Remove(charIndex + 1, currentLineLength - 1);
		//Ŭ�� ���� ó������ ���� ��ġ���� �����Ѵ�.
		clone->Remove(0, charIndex);
		//Ŭ�� ���� ���̿� ���� �� ���� �κ��� ������ �ٿ� �ִ´�.	
		endLine = Composite::GetAt(endLineOrder);
		currentLineLength = endLine->GetLength();
		endLine->Add(clone, currentLineLength);
		//Ŭ�� ���� �Ҵ������Ѵ�.
		delete clone;
	}
	//���� �ٰ� �������� �����Ѵ�.
	nextLine = Composite::GetAt(lineOrder + 1);
	//lineLength = currentLine->GetLength();
	currentLine->Add(nextLine, charIndex + 1);
	Composite::Remove(lineOrder + 1);
	//������ ���� ��ġ�� �����Ѵ�. 
	endLineOrder--;

	lastLine = paperToAdd->GetAt(paperToAdd->GetCurrent());
	lastLineLength = lastLine->GetLength();
	if (endLineOrder != lineOrder) {//������ ���� ���� �ٰ� ��ġ���� ������
		//������ ���� ������ ���� ������ ������ ���Ѵ�. 
		endCharIndex = lastLineLength - 1;
	}
	else {
		//�������� �ٿ��ֱ� ���� ��ġ�� ���Ѵ�. 
		endCharIndex = charIndex + lastLineLength;
	}

	lineOrder = Composite::Move(endLineOrder);
	currentLine = Composite::GetAt(lineOrder);
	currentLine->Move(endCharIndex);

	return lineOrder;
}

/*
* �Լ���Ī:Remove
* ���:�Է¹��� ������ �����Ѵ�. 
*/
Long Paper::Remove(Long startLineOrder, Long startCharIndex, Long endLineOrder, Long endCharIndex) {
	Glyph* startLine = 0;
	Glyph* endLine = 0;
	Long length = -1;

	//�� ������ �����´�. 
	startLine = Composite::GetAt(startLineOrder);
	if (startLineOrder == endLineOrder) {//�������� ���ٰ� ������ 
		startLine->Remove(startCharIndex + 1, endCharIndex);
	}
	else {//�����ٰ� ������ �ٸ���
		//�� ���ٿ��� ���� �ι��� �����.
		length = startLine->GetLength();
		startLine->Remove(startCharIndex + 1, length - 1);
		//�� ������ ���� �κ��� �����.
		endLine = Composite::GetAt(endLineOrder);
		endLine->Remove(0, endCharIndex);
		//�� ���ٿ� �� ������ ���δ�. 
		startLine->Add(endLine, startCharIndex + 1);
		//�ι��� �ٺ��� ������ �ٱ��� �����.
		Composite::Remove(startLineOrder + 1, endLineOrder);
	}
	//�������� ���� ��ġ�� �̵��Ѵ�.
	Long lineOrder;
	lineOrder = Composite::Move(startLineOrder);
	startLine = Composite::GetAt(lineOrder);
	startLine->Move(startCharIndex);

	return lineOrder;
}

/*
* �Լ���Ī:FindChar
* ���:�Է¹��� ���ڸ� ã�´�. 
*/
void Paper::FindChar(Glyph* characterToFind, Long*(*lineOrders), Long*(*charOrders), Long* count) {//���ڸ� �Է¹޴´�. 
	//������ ���� ���� ����Ѵ�. 
	Long charNumber = this->GetCharNumber();
	Glyph* currentLine = 0;
	Glyph* characterInPaper = 0;
	Long lineOrder = 0;
	Long paperLength = Composite::GetLength();
	Long lineLength;
	Long charOrder;
	BOOL result;
	Long i = 0;
	
	//���� �� ũ���� �迭�� �����. 
	*lineOrders = new Long[charNumber];
	*charOrders = new Long[charNumber];
	//������ �ʱ�ȭ�Ѵ�. 
	*count = 0;

	while (lineOrder < paperLength) {
		currentLine = Composite::GetAt(lineOrder);
		lineLength = currentLine->GetLength();
		charOrder = 0;
		while (charOrder < lineLength) {
			characterInPaper = currentLine->GetAt(charOrder);
			//������ �ڷ����� �°� ��ġ�ϴ��� Ȯ���Ѵ�.
			result = 0; //�ʱ�ȭ
			result = characterInPaper->IsEqual(characterToFind);
			//��ġ�ϸ�
			if (result == 1 && i < charNumber) { //ã������ 
				//���� ��ġ�� ����Ѵ�.
				(*lineOrders)[i] = lineOrder;
				(*charOrders)[i] = charOrder;
				(*count)++;
				i++;
			}
			charOrder++;
		}
		lineOrder++;
	}
}//ã�� ������ ��ȯ�Ѵ�. 

/*
* �Լ���Ī:FindCharUpperLower
* ���:�Է¹��� ������ �̱۹���Ʈ�� ��ҹ��� ���о��� �˻��Ѵ�. 
*/
void Paper::FindCharUpperLower(Glyph* characterToFind, Long* (*lineOrders), Long* (*charOrders), Long* count) {//���ڸ� �Է¹޴´�. 
	//������ ���� ���� ����Ѵ�. 
	Long charNumber = this->GetCharNumber();
	Glyph* currentLine = 0;
	Glyph* characterInPaper = 0;
	Long lineOrder = 0;
	Long paperLength = Composite::GetLength();
	Long lineLength;
	Long charOrder;
	BOOL result;
	Long i = 0;

	//���� �� ũ���� �迭�� �����. 
	*lineOrders = new Long[charNumber];
	*charOrders = new Long[charNumber];
	//������ �ʱ�ȭ�Ѵ�. 
	*count = 0;

	while (lineOrder < paperLength) {
		currentLine = Composite::GetAt(lineOrder);
		lineLength = currentLine->GetLength();
		charOrder = 0;
		while (charOrder < lineLength) {
			characterInPaper = currentLine->GetAt(charOrder);
			//������ �ڷ����� �°� ��ġ�ϴ��� Ȯ���Ѵ�.
			result = 0; //�ʱ�ȭ
			result = characterInPaper->IsEqualUpperLower(characterToFind);
			//��ġ�ϸ�
			if (result == 1 && i < charNumber) { //ã������ 
				//���� ��ġ�� ����Ѵ�.
				(*lineOrders)[i] = lineOrder;
				(*charOrders)[i] = charOrder;
				(*count)++;
				i++;
			}
			charOrder++;
		}
		lineOrder++;
	}
}//ã�� ������ ��ȯ�Ѵ�. 

/*
* �Լ���Ī:FindPaper
* ���:�Է��� ���̿� ��ġ�ϴ� ������ �ִ� ��ġ�� ã�´�.
*/
void Paper::FindPaper(Glyph* otherPaper, Long* (*lineOrders), Long* (*charIndexes), Long* count) { //ã�� ���̸� �Է¹޴´�.
	Long otherPaperLength = otherPaper->GetLength(); //ã�� ������ ���̸� ���Ѵ�. 
	Glyph* currentLine = 0;
	Long lineOrder = -1;
	Long charIndex = -2;
	Glyph* character = 0;
	Long otherPaperFirstLineLength = -1;
	Long otherPaperLastLineLength = -1;
	
	//���̿��� �� �ܾ�� ã�� ����
	Long(*lineOrdersOfChar) = 0;
	Long(*charOrders) = 0;
	Long countChar;
	//ã�� ���� ����
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
	
	//ã�� ������ �ʱ�ȭ�Ѵ�.
	*count = 0;
	//�˻������� �ִ� ���� ���Ѵ�. 
	maxLine = Composite::GetLength() - otherPaperLength;
	//ã�� ������ ������ ���Ǳ��̸� ���Ѵ�. 
	lineOrder = otherPaper->Last();
	currentLine = otherPaper->GetAt(lineOrder);
	otherPaperLastLineLength = currentLine->GetLength();
	//ã�� ������ ù��° ���� ���̸� ���Ѵ�.
	currentLine = otherPaper->GetAt(0);
	otherPaperFirstLineLength = currentLine->GetLength();

	//delete[] * lineOrders;
	//delete[] * charIndexes;
	//*lineOrders = NULL;
	//*charIndexes = NULL;

	if (otherPaperFirstLineLength > 0) { //ù��° �ٿ� ������ ������
		//ã�� ������ ù��° ���ڸ� ���̿��� ã�´�. 
		character = currentLine->GetAt(0);
		this->FindChar(character, &lineOrdersOfChar, &charOrders, &countChar);
		if (countChar > 0) { //ã������ ã�� ������ŭ ��ȯ �迭�� �Ҵ��Ѵ�. 
			*lineOrders = new Long[countChar];
			//*lineOrders = (Long(*))(calloc((size_t)countChar, (size_t)(sizeof(Long))));
			*charIndexes = new Long[countChar];
			while (i < countChar && lineOrdersOfChar[i] <= maxLine) { //�˻��� ������ŭ �׸��� �˻������� �ִ� �� ���� �ݺ��Ѵ�. 
				//�˻������� ������ ���� ���̸� Ȯ���Ѵ�. 
				lineOrder = lineOrdersOfChar[i];
				charIndex = charOrders[i] - 1;
				rangeLastLine = lineOrder + otherPaperLength - 1;
				currentLine = Composite::GetAt(rangeLastLine);
				lineLength = currentLine->GetLength();
				clone = 0;
				if (lineLength >= otherPaperLastLineLength && otherPaperLength <= 1) { //������ ���� ���̰� �˻� ���� ������ �� ���̺��� ũĿ�� ���� ���ٸ� �˻��ϸ� ���̸�
					//�˻������� �������� �����. 
					clone = this->Clone(lineOrder, charIndex, lineOrder, charIndex + otherPaperLastLineLength);
				}
				else if (lineLength >= otherPaperLastLineLength && otherPaperLength > 1) { //������ ���� ���̰� �˻� ���� ������ �� ���̺��� ũ�ų� ���� �������� �˻��ϸ�
					//�˻������� �������� �����. 
					clone = this->Clone(lineOrder, charIndex, lineOrder + otherPaperLength - 1, otherPaperLastLineLength - 1);
				}
				//�˻������� �������� �˻��ϴ� ���̿� ��ġ�ϴ��� Ȯ���Ѵ�. 
				result = 0;
				if (clone != 0) {
					result = clone->IsEqual(otherPaper);
				}
				if (result == 1) { //�˻������ ��ġ�ϸ� ��ġ�� ������ ����Ѵ�. 
					(*lineOrders)[j] = lineOrder;
					(*charIndexes)[j] = charIndex;
					(*count)++;
					j++;
				}
				//�������� �����. 
				delete clone;
				i++;
			}
		}
	}
	else { //ù��° �ٿ� ������ ������
		//�˻� ������ �� �� ��ŭ �Ҵ��Ѵ� 
		*lineOrders = new Long[maxLine];
		*charIndexes = new Long[maxLine];
		while (i <= maxLine) {//�˻� ������ �ټ� ��ŭ �ݺ��Ѵ�. 
			lineOrder = i;
			//�˻� ���� ���� ã�´�. 
			currentLine = Composite::GetAt(lineOrder);
			firstLineLastIndex = currentLine->GetLength() - 1;
			//�˻������� ������ ���� ���̸� Ȯ���Ѵ�. 
			lastLineOrder = lineOrder + otherPaperLength - 1;
			currentLine = Composite::GetAt(lastLineOrder);
			lineLength = currentLine->GetLength();
			clone = 0;
			if (lineLength >= otherPaperLastLineLength) { //������ ���� ���̰� �˻� ���� ������ �� ���̺��� ũ�ų� ������
				//�˻������� �������� �����. 
				clone = this->Clone(lineOrder, firstLineLastIndex, lastLineOrder, otherPaperLastLineLength - 1);
			}
			//�˻������� �������� �˻��ϴ� ���̿� ��ġ�ϴ��� Ȯ���Ѵ�. 
			result = 0;
			if (clone != 0) {
				result = clone->IsEqual(otherPaper);
			}
			if (result == 1 && j < maxLine) { //�˻������ ��ġ�ϸ� ��ġ�� ������ ����Ѵ�. 
				(*lineOrders)[j] = lineOrder;
				(*charIndexes)[j] = firstLineLastIndex;
				(*count)++;
				j++;
			}
			//�������� �����. 
			delete clone;
			i++;
		}
	}
	//������ �˻� �κ��� �Ҵ������Ѵ�.
	delete[] lineOrdersOfChar;
	delete[] charOrders;
}//ã�� ������ ��ȯ�Ѵ�. 

/*
* �Լ���Ī:FindPaperUpperLower
* ���:�Է��� ���̿� ��ġ�ϴ� ������ �ִ� ��ġ�� ã�´�.(��ҹ��� ���о���)
*/
void Paper::FindPaperUpperLower(Glyph* otherPaper, Long* (*lineOrders), Long* (*charIndexes), Long* count) { //ã�� ���̸� �Է¹޴´�.
	Long otherPaperLength = otherPaper->GetLength(); //ã�� ������ ���̸� ���Ѵ�. 
	Glyph* currentLine = 0;
	Long lineOrder = -1;
	Long charIndex = -2;
	Glyph* character = 0;
	Long otherPaperFirstLineLength = -1;
	Long otherPaperLastLineLength = -1;

	//���̿��� �� �ܾ�� ã�� ����
	Long(*lineOrdersOfChar) = 0;
	Long(*charOrders) = 0;
	Long countChar;
	//ã�� ���� ����
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

	//ã�� ������ �ʱ�ȭ�Ѵ�.
	*count = 0;
	//�˻������� �ִ� ���� ���Ѵ�. 
	maxLine = Composite::GetLength() - otherPaperLength;
	//ã�� ������ ������ ���Ǳ��̸� ���Ѵ�. 
	lineOrder = otherPaper->Last();
	currentLine = otherPaper->GetAt(lineOrder);
	otherPaperLastLineLength = currentLine->GetLength();
	//ã�� ������ ù��° ���� ���̸� ���Ѵ�.
	currentLine = otherPaper->GetAt(0);
	otherPaperFirstLineLength = currentLine->GetLength();

	//delete* lineOrders;
	//delete* charIndexes;

	if (otherPaperFirstLineLength > 0) { //ù��° �ٿ� ������ ������
		//ã�� ������ ù��° ���ڸ� ���̿��� ã�´�. 
		character = currentLine->GetAt(0);
		this->FindCharUpperLower(character, &lineOrdersOfChar, &charOrders, &countChar);
		if (countChar > 0) { //ã������ ã�� ������ŭ ��ȯ �迭�� �Ҵ��Ѵ�. 
			*lineOrders = new Long[countChar];
			*charIndexes = new Long[countChar];
			while (i < countChar && lineOrdersOfChar[i] <= maxLine) { //�˻��� ������ŭ �׸��� �˻������� �ִ� �� ���� �ݺ��Ѵ�. 
				//�˻������� ������ ���� ���̸� Ȯ���Ѵ�. 
				lineOrder = lineOrdersOfChar[i];
				charIndex = charOrders[i] - 1;
				rangeLastLine = lineOrder + otherPaperLength - 1;
				currentLine = Composite::GetAt(rangeLastLine);
				lineLength = currentLine->GetLength();
				clone = 0;
				if (lineLength >= otherPaperLastLineLength && otherPaperLength <= 1) { //������ ���� ���̰� �˻� ���� ������ �� ���̺��� ũĿ�� ���� ���ٸ� �˻��ϸ� ���̸�
					//�˻������� �������� �����. 
					clone = this->Clone(lineOrder, charIndex, lineOrder, charIndex + otherPaperLastLineLength);
				}
				else if (lineLength >= otherPaperLastLineLength && otherPaperLength > 1) { //������ ���� ���̰� �˻� ���� ������ �� ���̺��� ũ�ų� ���� �������� �˻��ϸ�
					//�˻������� �������� �����. 
					clone = this->Clone(lineOrder, charIndex, lineOrder + otherPaperLength - 1, otherPaperLastLineLength - 1);
				}
				//�˻������� �������� �˻��ϴ� ���̿� ��ġ�ϴ��� Ȯ���Ѵ�. 
				result = 0;
				if (clone != 0) {
					result = clone->IsEqualUpperLower(otherPaper);
				}
				if (result == 1) { //�˻������ ��ġ�ϸ� ��ġ�� ������ ����Ѵ�. 
					(*lineOrders)[j] = lineOrder;
					(*charIndexes)[j] = charIndex;
					(*count)++;
					j++;
				}
				//�������� �����. 
				delete clone;
				i++;
			}
		}
	}
	else { //ù��° �ٿ� ������ ������
		//�˻� ������ �� �� ��ŭ �Ҵ��Ѵ� 
		*lineOrders = new Long[maxLine];
		*charIndexes = new Long[maxLine];
		while (i <= maxLine) {//�˻� ������ �ټ� ��ŭ �ݺ��Ѵ�. 
			lineOrder = i;
			//�˻� ���� ���� ã�´�. 
			currentLine = Composite::GetAt(lineOrder);
			firstLineLastIndex = currentLine->GetLength() - 1;
			//�˻������� ������ ���� ���̸� Ȯ���Ѵ�. 
			lastLineOrder = lineOrder + otherPaperLength - 1;
			currentLine = Composite::GetAt(lastLineOrder);
			lineLength = currentLine->GetLength();
			clone = 0;
			if (lineLength >= otherPaperLastLineLength) { //������ ���� ���̰� �˻� ���� ������ �� ���̺��� ũ�ų� ������
				//�˻������� �������� �����. 
				clone = this->Clone(lineOrder, firstLineLastIndex, lastLineOrder, otherPaperLastLineLength - 1);
			}
			//�˻������� �������� �˻��ϴ� ���̿� ��ġ�ϴ��� Ȯ���Ѵ�. 
			result = 0;
			if (clone != 0) {
				result = clone->IsEqualUpperLower(otherPaper);
			}
			if (result == 1 && j < maxLine) { //�˻������ ��ġ�ϸ� ��ġ�� ������ ����Ѵ�. 
				(*lineOrders)[j] = lineOrder;
				(*charIndexes)[j] = firstLineLastIndex;
				(*count)++;
				j++;
			}
			//�������� �����. 
			delete clone;
			i++;
		}
	}
	//������ �˻� �κ��� �Ҵ������Ѵ�.
	delete[] lineOrdersOfChar;
	delete[] charOrders;
}//ã�� ������ ��ȯ�Ѵ�. 

/*
* �Լ���Ī:Clone
* ���:������Ÿ�� ���������� �����Ѵ�
*/
Glyph* Paper::Clone() {
	return new Paper(*this);
}
Glyph* Paper::Clone(Long startLineOrder, Long startCharIndex, Long endLineOrder, Long endCharIndex) { //������ ������ �Է¹޴´�.
	GlyphCreater glyphCreater;
	Glyph* clonePaper = 0;
	Glyph* line = 0;
	Glyph* currentLine = 0;
	Long lineOrder = -2;
	Long length = -1;
	//���̸� ����� ������ �ִ´�. 
	clonePaper = glyphCreater.Create("");
	line = glyphCreater.Create("\r\n");
	clonePaper->Add(line);
	//���� ���� �����´�. 
	currentLine = Composite::GetAt(startLineOrder);
	//���� ���� ù �ٿ� �����Ѵ�.(�������� �� ������ �Ǵ� ��츦 ����)
	line->Add(currentLine, 0);
	//���� ���� ���̿� �ִ´�. 
	lineOrder = startLineOrder + 1;
	while (lineOrder <= endLineOrder) {
		currentLine = Composite::GetAt(lineOrder);
		clonePaper->Add(currentLine->Clone());
		lineOrder++;
	}
	//������ �ٿ��� ������ ������ �ʴ� �κ��� �����Ѵ�. 
	lineOrder = clonePaper->Last();
	currentLine = clonePaper->GetAt(lineOrder);
	length = currentLine->GetLength();
	currentLine->Remove(endCharIndex + 1, length - 1);
	//ù �ٿ��� ������ ������ �ʴ� �κ��� �����Ѵ�. 
	lineOrder = clonePaper->First();
	currentLine = clonePaper->GetAt(lineOrder);
	currentLine->Remove(0, startCharIndex);

	return clonePaper; //���� ������ �������� ��ȯ�Ѵ�. 
}

/*
* �Լ���Ī:First
* ���:ó����ġ�� �̵��Ѵ�.
*/
Long Paper::First() {
	Long ret;
	Composite::First();
	ret = Composite::Next();
	return ret;
}

/*
* �Լ���Ī:Previous
* ���:������ġ�� �̵��Ѵ�.
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
* �Լ���Ī:SplitDummyLine
* ���:�����ٷ� �������� �����Լ�
*/
Long Paper::SplitDummyLine(Long lineOrder, Long characterIndex) {//���� ������ �ٿ��� �ڸ� ��ġ�� �Է¹޴´�. 
	GlyphCreater glyphCreater;
	Glyph* line = 0;
	Glyph* dummyLine = 0;
	Glyph* character = 0;
	Glyph* clone = 0;
	Long dummyLineOrder = -1;
	Long order = characterIndex;
	Long length = -1;
	Long i = 0;

	//���̿��� ������ ���� �����´�. 
	line = this->GetAt(lineOrder);
	//�� �������� �����. 
	dummyLine = glyphCreater.Create("\r");
	length = line->GetLength();
	while (i < length - order - 1) {//��ġ ������ �������� ���� ������ �ݺ��Ѵ�. 
		//��ġ ������ �ܾ �����´�. 
		character = line->GetAt(order + 1);
		//�ܾ��� Ŭ���� �����. 
		clone = character->Clone();
		//Ŭ���� �� �����ٿ� �ִ´�. 
		dummyLine->Add(clone);
		//�ٿ��� ��ġ ������ �ܾ �����Ѵ�. 
		line->Remove(order + 1);
		i++;
	}
	//�� �������� �� ������ ��ġ�� �ִ´�. 
	dummyLineOrder = Composite::Add(lineOrder + 1, dummyLine);
	//�� �������� ��ġ�� ��ȯ�Ѵ�.
	return dummyLineOrder;
}

/*
* �Լ���Ī:MergeAllDummyLines
* ���:��� �������� �����ٿ� �� ��ģ��.
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

	//������ ���̸� ���Ѵ�.
	paperLength = this->GetLength();
	//���̿��� ó���ٷ� �̵��Ѵ�.
	lineOrder = this->First();
	lineRet = this->GetAt(lineOrder);
	//��ȯ�� ���� �����ٷ� �����Ѵ�.
	currentLine = lineRet;
	//���� ���������� �̵��Ѵ�. 
	currentLine->Last();
	while (i < paperLength) {//���� ���������϶����� �ݺ��Ѵ�.
		if (dynamic_cast<DummyLine*>(lineRet)) {
			//���� �������̸� ���� �ٰ� �����Ѵ�.
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
			//���� �������� �ƴϸ� ���� �ٷ� �����Ѵ�. 
			currentLine = lineRet;
			currentLine->Last();
		}
		//���̿��� �����ٷ� �̵��Ѵ�. 
		lineOrder = this->Next();
		lineRet = GetAt(lineOrder);
		i++;
	}
}

/*
* �Լ���Ī:MergeDummyLines
* ���:�������� �����ٿ� ��ġ�� �Լ��� �����Լ�
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

	//���̿��� �������� ��ġ�� �̵��Ѵ�.
	startlineOrder = this->Move(startlineOrder);
	//�������� �����´�. 
	startLine = this->GetAt(startlineOrder);
	//�����ٿ��� ������ �̵��Ѵ�.
	startLine->Last();
	//�������� �����´�. 
	previousLineOrder = startlineOrder;
	lineOrder = this->Next();
	currentLine = this->GetAt(lineOrder);
	
	while (lineOrder != previousLineOrder && dynamic_cast<DummyLine*>(currentLine)) {
		previousCharOrder = -1;
		currentLine->First();
		charIndex = currentLine->Next();
		while (charIndex != previousCharOrder) {
			//���� ������ �ܾ �����´�. 
			character = currentLine->GetAt(charIndex);
			//�ܾ��� ���纻�� ���� �ٿ� �ִ´�. 
			clone = character->Clone();
			startLine->Add(clone);
			//���� �ܾ���ġ������ �̵��Ѵ�.
			previousCharOrder = charIndex;
			charIndex = currentLine->Next();
		}
		//�������� �����´�. 
		previousLineOrder = lineOrder;
		lineOrder = this->Next();
		currentLine = this->GetAt(lineOrder);
		//�����ټ��� ����
		countRepeat++;
	}
	while (i < countRepeat) { //�����ټ���ŭ �ݺ��Ѵ�. 
		Composite::Remove(startlineOrder + 1);
		i++;
	}
	//���̿��� �������� ��ġ�� �̵��Ѵ�.
	startlineOrder = this->Move(startlineOrder);
	//�������� ��ġ�� ��ȯ�Ѵ�. 
	return startlineOrder;
}

/*
* �Լ���Ī:GetLocation
* ���:���� ��ġ�� ���Ѵ�.
*/
void Paper::GetLocation(Long lineOrder, Long charIndex, Long* lineLocation, Long* charLocation) { //���� ������ ��ġ�� �Է¹޴´�
	Glyph* currentLine = 0;
	Glyph* lineToFind = 0;
	Long lineLength; //���� ����
	Long lineIndexNumber; //���� ��ġ ����
	Long lineCount = 0;
	
	*charLocation = charIndex;
	lineOrder = this->Move(lineOrder);
	currentLine = this->GetAt(lineOrder);
	while (dynamic_cast<DummyLine*>(currentLine)) { //���� �������� �ƴ� �� ���� �ݺ��Ѵ�.
		//���� �ٷ� �̵��Ѵ�. 
		lineOrder = this->Previous();
		currentLine = this->GetAt(lineOrder);
		//�� ��ġ���� �����Ѵ�.
		lineLength = currentLine->GetLength();
		lineIndexNumber = lineLength;
		*charLocation = *charLocation + lineIndexNumber;
	}
	//���̿��� ã�� ���� ����(�������� �� ����)�� ���Ѵ�.
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
	*lineLocation = lineCount - 1; //������ ���Ѵ�.
}//���� ������ �� ��ġ�� ��ȯ�Ѵ�.

/*
* �Լ���Ī:MoveToLocation
* ���:���� ��ġ�� �̵��Ѵ�.
*/
void Paper::MoveToLocation(Long lineLocation, Long charLocation, Long* lineOrder, Long* charIndex) { //���� ��ġ�� �� ��ġ�� �Է¹޴´�.
	Glyph* currentLine = 0;
	Long lineCount = 1;
	Long lineLength;
	Long i = 1;

	//���̿��� ���� ��ġ�� ���� �����´�. 
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
		while (*charIndex > lineLength - 1) {//���� ���̰� �� ��ġ���� ���� ���� �ݺ��Ѵ�.
			//�� ��ġ�� �����Ѵ�.
			*charIndex = *charIndex - lineLength;
			//�����ٷ� �̵��Ѵ�.
			*lineOrder = this->Next();
			currentLine = this->GetAt(*lineOrder);
			lineLength = currentLine->GetLength();
		}
		//�ٿ��� ���ŵ� ��ġ�� �̵��Ѵ�.
		currentLine->Move(*charIndex);
	}
} //���� ���� ��ġ�� ���ŵ� �� ��ġ�� ��ȯ�Ѵ�.

/*
* �Լ���Ī:GetString
* ���:���� ���ڸ� �����´�.
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
* �Լ���Ī:GetExactString
* ���:������ ���� �ڷᱸ���� ����� ��Ȯ�� �ƽ�Ű�ڵ��� ���ڸ� ���ڿ��� �����Ͽ� ����Ѵ�.
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
* �Լ���Ī:Accept
* ���:Element�μ� Visitor�� Visit�� ����Ѵ�.
*/
void Paper::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

/*
* �Լ���Ī:IsEqual
* ���:�Է°��� ������ ���Ѵ�
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
* �Լ���Ī:IsEqualUpperLower
* ���:��ҹ��� ���� ���ϰ� ������ ã�´�. 
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
* �Լ���Ī:IsNotEqual
* ���:�Է°��� �ٸ��� ���Ѵ�
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
* �Լ���Ī:GetCharNumber
* ���:���� ���� ���ڼ��� ����Ͽ� ��ȯ�Ѵ�.
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
* �Լ���Ī:operator=
* ���:ġȯ������
*/
Paper& Paper::operator=(const Paper& source) {
	Composite::operator=(source);
	return *this;
}

/*
* �Լ���Ī:operator[]
* ���:÷�ڿ�����
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

	//�⺻ �׽�Ʈ�� ����
	paper = glyphCreater.Create("");
	line = glyphCreater.Create("\r\n");
	indexLine = paper->Add(line);
	lineReturn = paper->GetAt(indexLine);
	character = glyphCreater.Create("��");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());
	character = glyphCreater.Create("��");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());
	character = glyphCreater.Create("��");
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

#if 0 //�̵� �׽�Ʈ �ڵ�
	cout << endl << "�� �̵�" << endl;
	cout << endl << "First" << endl;
	current = paper->First();
	//!!!!!!!!!!! �� ó���� ���� 0���� ������???
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

	//���� �̵�
	cout << endl << "���� �̵�" << endl;
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

	cout << endl << "���� ���ڷ� �̵�" << endl;
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

	cout << endl << "���� ���ڷ� �̵�" << endl;
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
	current = lineReturn->NextWord(); //�ߺ� ��� �׽�Ʈ
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
#endif //�̵� �׽�Ʈ �ڵ�

#if 0 // �������� �׽�Ʈ �ڵ�
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
	character = glyphCreater.Create("��");
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
#endif // �������� �׽�Ʈ �ڵ�

#if 0 //����� �׽�Ʈ �ڵ�
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
#endif //����� �׽�Ʈ �ڵ�

#if 0//�� ������ �� ��ġ�� �׽�Ʈ
	cout << endl << "�� ��ġ��" << endl;
	//�� ��ġ��
	indexLine = paper->Move(0);
	lineReturn = paper->GetAt(indexLine);
	nextLine = paper->GetAt(1);
	//ù��° �� ���� �ι�° ���� ���δ�
	current = lineReturn->AppendLineFromRear(nextLine);
	cout << current;
	cout << endl << static_cast<string>(paper->GetString()) << endl;
	
	//�ι�° ���� �����. 
	paper->Remove(1);
	cout << endl << static_cast<string>(paper->GetString()) << endl;

	//�� ������
	cout << endl << "�� ������" << endl;
	//ù��° ���� 4��° ��ġ�� �������� ������. 
	tempLine = lineReturn->SplitLineRearAsLine(3);
	paper->Add(1, tempLine);
	cout << endl << static_cast<string>(paper->GetString()) << endl;
#endif

#if 0 //���̶��� �׽�Ʈ
	cout << endl << "���� ���� �׽�Ʈ" << endl;
	cout << "���� ���� �и�" << endl;
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

	cout << "���� ���� ����" << endl;
	//���� �� ����
	paper->MergeDummyLines(3);
	cout << endl << static_cast<string>(paper->GetString()) << endl;

	//��ü �� ����
	//paper->MergeAllDummyLines();
	//cout << endl << static_cast<string>(paper->GetString()) << endl;
#endif//���̶��� �׽�Ʈ

#if 0 //���� ��ġ �׽�Ʈ
	//���̶��� �׽��� ��ģ ���� ��ġ �׽�Ʈ
	Long lineLocation = -99; //���� ���� ����(�������� ������ ����)
	Long charLocation = -99; //���� ��ġ(�������� ������ ������ ����)
	Long lineOrder = -1;
	Long charIndex = -2;

	cout << endl << "���� ��ġ �׽�Ʈ" << endl;
	//�Ǿ����� �̵� �� ���� ��ġ�� ����Ѵ�.
	cout << "�� �� ���� �̵�" << endl;
	lineOrder = 0;
	charIndex = -1;
	paper->Move(lineOrder);
	paper->GetAt(lineOrder)->Move(charIndex);
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "GetLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	paper->GetLocation(lineOrder, charIndex, &lineLocation, &charLocation);
	cout << "GetLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	
	cout << "���� �и�" << endl;
	indexLine = paper->SplitDummyLine(0, 2);
	cout << static_cast<string>(paper->GetString()) << endl;
	
	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "���� ��ġ�� �̵�" << endl;
	paper->MoveToLocation(lineLocation, charLocation, &lineOrder, &charIndex);
	cout << "MoveToLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << endl;



	//�� �ڷ� �̵� �� ���� ��ġ�� ����Ѵ�.
	cout << "�� �ڷ� �̵�" << endl;
	//lineOrder = 0;
	//charIndex = -1;
	lineOrder = paper->Last();
	charIndex = paper->GetAt(lineOrder)->Last();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "GetLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	paper->GetLocation(lineOrder, charIndex, &lineLocation, &charLocation);
	cout << "GetLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;

	cout << "���� �и�" << endl;
	indexLine = paper->SplitDummyLine(1, 2);
	cout << static_cast<string>(paper->GetString()) << endl;

	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;

	cout << "���� ��ġ�� �̵�" << endl;
	paper->MoveToLocation(lineLocation, charLocation, &lineOrder, &charIndex);
	cout << "MoveToLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << endl;



	//4��° �� 2��° ��ġ�� �̵��� ���� ��ġ�� ����Ѵ�.
	cout << "4��° �� 2��° ��ġ�� �̵�" << endl;
	lineOrder = 3;
	charIndex = 1;
	paper->Move(lineOrder);
	paper->GetAt(lineOrder)->Move(charIndex);
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "GetLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	paper->GetLocation(lineOrder, charIndex, &lineLocation, &charLocation);
	cout << "GetLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;

	cout << "���� �и�" << endl;
	indexLine = paper->SplitDummyLine(3, 1);
	cout << static_cast<string>(paper->GetString()) << endl;

	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "���� ��ġ�� �̵�" << endl;
	paper->MoveToLocation(lineLocation, charLocation, &lineOrder, &charIndex);
	cout << "MoveToLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << endl;


	
	//5��° ���� ������ �̵� �� ���� ��ġ�� ����Ѵ�.
	cout << "5��° ���� ������ �̵� �� ���� ��ġ�� ����Ѵ�." << endl;
	lineOrder = 4;
	charIndex = 1;
	paper->Move(lineOrder);
	paper->GetAt(lineOrder)->Move(charIndex);
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "GetLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	paper->GetLocation(lineOrder, charIndex, &lineLocation, &charLocation);
	cout << "GetLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;

	cout << "���� ����" << endl;
	paper->MergeAllDummyLines();
	cout << static_cast<string>(paper->GetString()) << endl;

	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "���� ��ġ�� �̵�" << endl;
	paper->MoveToLocation(lineLocation, charLocation, &lineOrder, &charIndex);
	cout << "MoveToLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << endl;

	//ù��° ���� 5��° ��ġ�� �̵� �� ���� ��ġ�� ����Ѵ�.
	cout << "ù��° ���� 5��° ��ġ�� �̵� �� ���� ��ġ�� ����Ѵ�." << endl;
	lineOrder = 0;
	charIndex = 4;
	paper->Move(lineOrder);
	paper->GetAt(lineOrder)->Move(charIndex);
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "GetLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	paper->GetLocation(lineOrder, charIndex, &lineLocation, &charLocation);
	cout << "GetLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;

	indexLine = paper->SplitDummyLine(0, 2);
	cout << static_cast<string>(paper->GetString()) << endl;

	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "���� ��ġ�� �̵�" << endl;
	paper->MoveToLocation(lineLocation, charLocation, &lineOrder, &charIndex);
	cout << "MoveToLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << endl;



	//����° ���� 3��° ��ġ�� �̵� �� ���� ��ġ�� ����Ѵ�.
	cout << "����° ���� 3��° ��ġ�� �̵� �� ���� ��ġ�� ����Ѵ�." << endl;
	lineOrder = 2;
	charIndex = 2;
	paper->Move(lineOrder);
	paper->GetAt(lineOrder)->Move(charIndex);
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "GetLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	paper->GetLocation(lineOrder, charIndex, &lineLocation, &charLocation);
	cout << "GetLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;

	//��ü �� ����
	cout << "���� ����" << endl;
	paper->MergeAllDummyLines();
	cout << static_cast<string>(paper->GetString()) << endl;

	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << "���� ��ġ�� �̵�" << endl;
	paper->MoveToLocation(lineLocation, charLocation, &lineOrder, &charIndex);
	cout << "MoveToLocation �Լ� ��:" << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << "\t" << "lineLocation:" << lineLocation << "\t" << "charLocation:" << charLocation << endl;
	lineOrder = paper->GetCurrent();
	charIndex = paper->GetAt(lineOrder)->GetCurrent();
	cout << "lineOrder:" << lineOrder << "\t" << "charIndex:" << charIndex << endl;
	cout << endl;
#endif //���� ��ġ �׽�Ʈ 

#if 0 //���� �ܰ� Add Remove �׽�Ʈ
	cout << endl << "Add �׽�Ʈ - Line" << endl;
	//���̸� �����Ѵ�.
	Glyph* otherPaper = paper->Clone();
	//2��° ���� 2��° ��ġ�� ���纻�� ù��°���� �ִ´�.
	Glyph* otherLine = otherPaper->GetAt(0);
	lineReturn = paper->GetAt(1);
	indexCharacter = lineReturn->Add(otherLine, 1);
	cout << "CharIndex : " << indexCharacter << endl;
	cout << lineReturn->GetString() << endl;
	//������ 2��° �ٿ� ������ ���̸� �����Ѵ�.
	cout << endl << "Add �׽�Ʈ - Paper" << endl;
	indexLine = paper->Add(otherPaper, 1);
	cout << "LineIndex : " << indexLine << endl;
	cout << paper->GetString() << endl;

	cout << endl << "Remove �׽�Ʈ - Paper - �� " << endl;
	indexLine = paper->Remove(5, 5);
	cout << "LineIndex : " << indexLine << endl;
	cout << paper->GetString() << endl;

	cout << endl << "Remove �׽�Ʈ - Paper - �߰� " << endl;
	indexLine = paper->Remove(1, 2);
	cout << "LineIndex : " << indexLine << endl;
	cout << paper->GetString() << endl;

	cout << endl << "Remove �׽�Ʈ - Paper - �Ǿ� " << endl;
	indexLine = paper->Remove(0, 1);
	cout << "LineIndex : " << indexLine << endl;
	indexLine = paper->Move(0);
	cout << "LineIndex : " << indexLine << endl;
	cout << paper->GetString() << endl;

	cout << endl << "Remove �׽�Ʈ - Line - �߰� " << endl;
	lineReturn = paper->GetAt(0);
	indexCharacter = lineReturn->Remove(2, 6);
	cout << "CharIndex : " << indexCharacter << endl;
	cout << lineReturn->GetString() << endl;

	cout << endl << "Remove �׽�Ʈ - Line - �ǵ� " << endl;
	indexCharacter = lineReturn->Remove(6, 7);
	cout << "CharIndex : " << indexCharacter << endl;
	cout << lineReturn->GetString() << endl;

	cout << endl << "Remove �׽�Ʈ - Line - ���� " << endl;
	indexCharacter = lineReturn->Remove(0, 5);
	cout << "CharIndex : " << indexCharacter << endl;
	cout << lineReturn->GetString() << endl;

	cout << endl << "Remove �׽�Ʈ - Line - ���� �������� Ȯ��" << endl;
	character = glyphCreater.Create("��");
	indexCharacter = lineReturn->Add(character);
	cout << lineReturn->GetString() << endl;

#endif //���� �ܰ� Add Remove �׽�Ʈ

//#if 0 //Find �׽�Ʈ
	Glyph* temp = paper->Clone();
	tempLine = glyphCreater.Create("\r\n");
	temp->Add(0, tempLine);

	paper->Add(paper, 3);
	paper->Add(paper, 6);
	cout << endl << static_cast<string>(paper->GetString()) << endl << endl;

	//ABC�� �˻�
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
		cout << i + 1 << "��°" << endl;
		cout << "��:" << lineOrders[i] << "\t" << "������ġ:" << charIndexes[i] << endl << endl;
		i++;
	}
	cout << endl;
	delete[] lineOrders;
	delete[] charIndexes;
	currentLine->Remove(0, 2);
	
	//�� 12 �� ã�´�. 
	character = glyphCreater.Create("��");
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
		cout << i + 1 << "��°" << endl;
		cout << "��:" << lineOrders[i] << "\t" << "������ġ:" << charIndexes[i] << endl << endl;
		i++;
	}
	cout << endl;
	delete[] lineOrders;
	delete[] charIndexes;
	currentLine->Remove(0, 3);

	//����
	// A�� ã�´�. 
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
		cout << i + 1 << "��°" << endl;
		cout << "��:" << lineOrders[i] << "\t" << "������ġ:" << charIndexes[i] << endl << endl;
		i++;
	}
	cout << endl;
	delete[] lineOrders;
	delete[] charIndexes;
	currentLine->Remove(0, 1);

	//����
	// A�� ã�´�. 
	character = glyphCreater.Create("A");
	currentLine->Add(character);
	cout << static_cast<string>(currentLine->GetString()) << endl;

	paper->FindPaperUpperLower(paperToFind, &lineOrders, &charIndexes, &count);
	i = 0;
	while (i < count) {
		cout << i + 1 << "��°" << endl;
		cout << "��:" << lineOrders[i] << "\t" << "������ġ:" << charIndexes[i] << endl << endl;
		i++;
	}
	cout << endl;
	delete[] lineOrders;
	delete[] charIndexes;
	currentLine->Remove(0, 0);
	paperToFind->Remove(1);

//#endif //Find �׽�Ʈ

	paper->FindPaper(temp, &lineOrders, &charIndexes, &count);
	i = 0;
	while (i < count) {
		cout << i + 1 << "��°" << endl;
		cout << "��:" << lineOrders[i] << "\t" << "������ġ:" << charIndexes[i] << endl << endl;
		i++;
	}
	cout << endl;
	delete[] lineOrders;
	delete[] charIndexes;

	return 0;
}
