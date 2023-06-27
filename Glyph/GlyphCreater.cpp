//GlyphCharacter.cpp
/*
* 파일명칭:GlyphCharacter.cpp
* 기능:문자 클래스를 생성하는 팩토리 클래스
* 작성자:허지욱
* 작성일자:2022/8/23
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
* 함수명칭:GlyphCreater
* 기능:생성자
*/
GlyphCreater::GlyphCreater() {
}

/*
* 함수명칭:~GlyphCreater
* 기능:소멸자
*/
GlyphCreater::~GlyphCreater() {
}

/*
* 함수명칭:Create
* 기능:글자를 만들어 반환한다. 
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
		while (j < stringLength) {//줄의 길이만큼 반복한다. 
			//한글 영문 구분을 한다. 
			//(lineLoaded[i] & 0x80)이 TRUE이면 범위 안에 속해있다는 의미이며 아스키 범주 안이라는 의미이다.

			if ((contents[j] & 0x80) == 0) {//영문이면 문자에 영문을 적는다.
				singleByte[0] = contents[j];
				character = this->Create(singleByte);
			}
			//한글이면 다음바이트까지 포함해서 문자에 한글을 적는다.
			else {
				doubleByte[0] = contents[j];
				j++; // 다음 문자로 이동한다.
				doubleByte[1] = contents[j];
				character = this->Create(doubleByte);
			}
			//문자를 줄에 적는다.
			ret->Add(character);
			j++; //다음 문자로 이동한다. 
		}
	}
#endif
	//else {
	ret = this->Create("");
	currentLine = this->Create("\n");
	ret->Add(currentLine);
	while (j < stringLength && contents[j] != '\0') {//줄의 길이만큼 반복한다. 
		//한글 영문 구분을 한다. 
		//(lineLoaded[i] & 0x80)이 TRUE이면 범위 안에 속해있다는 의미이며 아스키 범주 안이라는 의미이다.

		if ((contents[j] & 0x80) == 0 && contents[j] != '\n' && contents[j] != '\r' && contents[j] != '\0') {//영문이면 문자에 영문을 적는다. //
			singleByte[0] = contents[j];
			character = this->Create(singleByte);
			//문자를 줄에 적는다.
			currentLine->Add(character);
		}
		//한글이면 다음바이트까지 포함해서 문자에 한글을 적는다.
		else if ((contents[j] & 0x80) == 0 && (contents[j] == '\n' || contents[j] == '\r') && contents[j] != '\0') { //
			currentLine = this->Create("\n");
			ret->Add(currentLine);
			j++;
		}
		else if (contents[j] != '\0') {
			doubleByte[0] = contents[j];
			j++; // 다음 문자로 이동한다.
			doubleByte[1] = contents[j];
			character = this->Create(doubleByte);
			//문자를 줄에 적는다.
			currentLine->Add(character);
		}
		j++; //다음 문자로 이동한다. 
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
	character = glyphCreater.Create("가");
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

	character = glyphCreater.Create("나");
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

	character = glyphCreater.Create("라");
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