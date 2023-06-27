//GlyphCharacter.cpp
/*
* ���ϸ�Ī:GlyphCharacter.cpp
* ���:���� Ŭ������ �����ϴ� ���丮 Ŭ����
* �ۼ���:������
* �ۼ�����:2022/8/23
*/
#include "GlyphCreater.h"
#include "Glyph.h"
#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include<string>
using namespace std;

/*
* �Լ���Ī:GlyphCreater
* ���:������
*/
GlyphCreater::GlyphCreater() {
}

/*
* �Լ���Ī:~GlyphCreater
* ���:�Ҹ���
*/
GlyphCreater::~GlyphCreater() {
}

/*
* �Լ���Ī:Create
* ���:���ڸ� ����� ��ȯ�Ѵ�. 
*/
Glyph* GlyphCreater::Create(const char(*contents)) {
	Glyph* ret = 0;
	char singleByte;
	char doubleByte[2];

	if (contents == "") {
		ret = new Paper;
	}
	else if ((contents[0] & 0x80) == 0 && (contents == "\r\n" || contents == "\n\r" || contents == "\n")) {
		ret = new Line;
	}
	else if ((contents[0] & 0x80) == 0 && contents == "\r") {
		ret = new DummyLine;
	}
	else if ((contents[0] & 0x80) != 0) {
		doubleByte[0] = contents[0];
		doubleByte[1] = contents[1];
		ret = new DoubleByteCharacter(doubleByte);
	}
	else if ((contents[0] & 0x80) == 0) {
		singleByte = contents[0];
		ret = new SingleByteCharacter(singleByte);
	}

	return ret;
}
Glyph* GlyphCreater::Create(string contents) {
	Glyph* ret = NULL;
	Glyph* currentLine = NULL;
	Glyph* character = NULL;
	char singleByte[1];
	char doubleByte[2];
	int stringLength = contents.length();

	int i = 0;
	int j = 0;

#if 0
	while (i < stringLength && contents[i] != '\n') {
		i++;
	}
	if (i > stringLength) {
		ret = new Line;
		while (j < stringLength) {//���� ���̸�ŭ �ݺ��Ѵ�. 
			//�ѱ� ���� ������ �Ѵ�. 
			//(lineLoaded[i] & 0x80)�� TRUE�̸� ���� �ȿ� �����ִٴ� �ǹ��̸� �ƽ�Ű ���� ���̶�� �ǹ��̴�.

			if ((contents[j] & 0x80) == 0) {//�����̸� ���ڿ� ������ ���´�.
				singleByte[0] = contents[j];
				character = this->Create(singleByte);
			}
			//�ѱ��̸� ��������Ʈ���� �����ؼ� ���ڿ� �ѱ��� ���´�.
			else {
				doubleByte[0] = contents[j];
				j++; // ���� ���ڷ� �̵��Ѵ�.
				doubleByte[1] = contents[j];
				character = this->Create(doubleByte);
			}
			//���ڸ� �ٿ� ���´�.
			ret->Add(character);
			j++; //���� ���ڷ� �̵��Ѵ�. 
		}
	}
#endif
	//else {
	ret = this->Create("");
	currentLine = this->Create("\n");
	ret->Add(currentLine);
	while (j < stringLength && contents[j] != '\0') {//���� ���̸�ŭ �ݺ��Ѵ�. 
		//�ѱ� ���� ������ �Ѵ�. 
		//(lineLoaded[i] & 0x80)�� TRUE�̸� ���� �ȿ� �����ִٴ� �ǹ��̸� �ƽ�Ű ���� ���̶�� �ǹ��̴�.

		if ((contents[j] & 0x80) == 0 && contents[j] != '\n' && contents[j] != '\r' && contents[j] != '\0') {//�����̸� ���ڿ� ������ ���´�. //
			singleByte[0] = contents[j];
			character = this->Create(singleByte);
			//���ڸ� �ٿ� ���´�.
			currentLine->Add(character);
		}
		//�ѱ��̸� ��������Ʈ���� �����ؼ� ���ڿ� �ѱ��� ���´�.
		else if ((contents[j] & 0x80) == 0 && (contents[j] == '\n' || contents[j] == '\r') && contents[j] != '\0') { //
			currentLine = this->Create("\n");
			ret->Add(currentLine);
			j++;
		}
		else if (contents[j] != '\0') {
			doubleByte[0] = contents[j];
			j++; // ���� ���ڷ� �̵��Ѵ�.
			doubleByte[1] = contents[j];
			character = this->Create(doubleByte);
			//���ڸ� �ٿ� ���´�.
			currentLine->Add(character);
		}
		j++; //���� ���ڷ� �̵��Ѵ�. 
	}
	//}

	string temp = ret->GetString();

	return ret;
}




#if 0
#include <iostream>
int main(int argc, char* argv[]) {
	GlyphCreater glyphCreater;
	Glyph* paper = 0;
	Glyph* line = 0;
	Glyph* lineReturn = 0;
	Glyph* character = 0;
	Glyph* characterReturn = 0;
	int indexLine = -1;
	int indexCharacter = -1;

	paper = glyphCreater.Create("");
	line = glyphCreater.Create("\r\n");
	indexLine = paper->Add(line);
	lineReturn = paper->GetAt(indexLine);
	character = glyphCreater.Create("��");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());

	character = glyphCreater.Create("A");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());

	line = glyphCreater.Create("\r\n");
	indexLine = paper->Add(line);
	lineReturn = paper->GetAt(indexLine);
	cout << endl;

	character = glyphCreater.Create("��");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());

	character = glyphCreater.Create("B");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());

	character = glyphCreater.Create("4");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());

	character = glyphCreater.Create("5");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());

	line = glyphCreater.Create("\r\n");
	indexLine = paper->Add(line);
	lineReturn = paper->GetAt(indexLine);
	cout << endl;

	character = glyphCreater.Create("��");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());

	character = glyphCreater.Create("D");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());

	character = glyphCreater.Create("7");
	indexCharacter = lineReturn->Add(character);
	characterReturn = lineReturn->GetAt(indexCharacter);
	cout << static_cast<string>(characterReturn->GetString());

	return 0;
}
#endif