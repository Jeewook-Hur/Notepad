//Document.cpp
/*
* 파일명칭:Document.cpp
* 기능:입력받은 문서를 저장하는 파일의 헤더
* 작성자:허지욱
* 작성일자:20220819
*/
#include "Document.h"
#include "Paper.h"
#include "Line.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "GlyphCreater.h"
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

/*
* 함수명칭:Document
* 기능:생성자
*/
Document::Document(string path, string name, string extention)
	:path(path), name(name), extention(extention) {
}
Document::Document(const Document& source) {
	this->path = source.path;
	this->name = source.name;
	this->extention = source.extention;
}

/*
* 함수명칭:~Document
* 기능:소멸자
*/
Document::~Document() {
}

/*
* 함수명칭:Load
* 기능:적재하다
*/
Glyph* Document::Load() {
	fstream file;
	string fileName;
	GlyphCreater glyphCreater;
	Glyph* paper = 0;
	Glyph* line = 0;
	Glyph* character = 0;
	char lineLoaded[10000];
	char singleByte[1];
	char doubleByte[2];
	int i;
	
	//종이를 만든다. 
	paper = glyphCreater.Create("");

	//경로에 위치한 문서를 연다
	fileName = this->path + "//" + this->name + "." + this->extention;
	file.open(fileName, ios::in);

	while (!file.eof()) {//문서의 끝이 아닌동안 반복한다. 
		//문서에서 줄을 읽는다. 
		file.getline(lineLoaded, 10000);
		line = glyphCreater.Create("\r\n");
		paper->Add(line);
		i = 0;
		while (lineLoaded[i] != '\0' && i < 10000) {//줄의 길이만큼 반복한다. 
			//한글 영문 구분을 한다. 
			//(lineLoaded[i] & 0x80)이 TRUE이면 범위 안에 속해있다는 의미이며 아스키 범주 안이라는 의미이다.

			if ((lineLoaded[i] & 0x80) == 0) {//영문이면 문자에 영문을 적는다.
				singleByte[0] = lineLoaded[i];
				character = glyphCreater.Create(singleByte);
			}
			//한글이면 다음바이트까지 포함해서 문자에 한글을 적는다.
			else {
				doubleByte[0] = lineLoaded[i];
				i++; // 다음 문자로 이동한다.
				doubleByte[1] = lineLoaded[i];
				character = glyphCreater.Create(doubleByte);
			}
			//문자를 줄에 적는다.
			line->Add(character);
			i++; //다음 문자로 이동한다. 
		}
		//문서에서 줄을 읽는다. 
		//file.getline(lineLoaded, 1024);
	}
	if (paper->GetLength() == 0) {
		line = glyphCreater.Create("\r\n");
		paper->Add(line);
	}
	file.close();
	return paper;
}

/*
* 함수명칭:Save
* 기능:저장하다
*/
void Document::Save(Glyph* paper) {
	fstream file;
	Glyph* line = 0;
	string fileName;
	string lineString;
	char lineCharacter[10000];
	int paperLength = -1;
	int charLength = 0;
	int i = 0;
	int j; //반복 제어 변수
	int k; //첨자

	//경로의 폴더에 문서를 만든다
	if (this->path == "") {
		fileName = this->name + "." + this->extention;
	}
	else {
		fileName = this->path + "//" + this->name + "." + this->extention;
	}
	//문서를 연다
	file.open(fileName, ios::out);
	
	paperLength = paper->GetLength();
	while (i < paperLength) { //종이의 길이만큼 반복한다. 
		//현재 위치의 줄을 가져온다. 
		line = paper->GetAt(i);
		//줄의 내용을 문서에 적는다. 
		lineString = line->GetExactString();
		//내용을 문자 배열에 옮겨적는다. 
		k = 0;
		j = 0;
		charLength = lineString.length();
		while (j < charLength) { //내용의 길이만큼 반복한다. 
			lineCharacter[k] = lineString[k];
			k++;
			j++;
		}
		//문자 배열을 파일에 적는다.
		file.write(lineCharacter, charLength);
		if (i < paperLength - 1) {
			//파일의 줄을 바꾼다.
			file << endl;
		}
		i++;
	}
	//파일을 닫는다.
	file.close();
}

#if 0

#include <iostream>
using namespace std;
int main(int argc, char* argv[]) {
	Document* document;
	Glyph* paper;
	Glyph* line = NULL;
	Glyph* character = NULL;
	Long indexLine = -1;
	string paperString;
#if 0
	//종이를 만든다.
	paper = new Paper;
	//종이에 줄을 삽입한다.
	line = new Line;
	indexLine = paper->Add(line);

	//종이에 '가'를 삽입한다.
	character = new DoubleByteCharacter((char*)"가");
	line = paper->GetAt(indexLine);
	line->Add(character);

	//종이에 'A'를 삽입한다.
	character = new SingleByteCharacter((char)'A');
	line = paper->GetAt(indexLine);
	line->Add(character);

	//종이에 줄을 삽입한다.
	line = new Line;
	indexLine = paper->Add(line);
	//종이에 '나'를 삽입한다.
	character = new DoubleByteCharacter((char*)"나");
	line = paper->GetAt(indexLine);
	line->Add(character);

	//종이에 'B'를 삽입한다.
	character = new SingleByteCharacter((char)'B');
	line = paper->GetAt(indexLine);
	line->Add(character);

	//종이에 '4'를 삽입한다.
	character = new SingleByteCharacter((char)'4');
	line = paper->GetAt(indexLine);
	line->Add(character);

	//종이에 '5'를 삽입한다.
	character = new SingleByteCharacter((char)'5');
	line = paper->GetAt(indexLine);
	line->Add(character);

	//종이에 줄을 삽입한다.
	line = new Line;
	indexLine = paper->Add(line);
	//종이에 '라'를 삽입한다.
	character = new DoubleByteCharacter((char*)"라");
	line = paper->GetAt(indexLine);
	line->Add(character);

	//종이에 'D'를 삽입한다.
	character = new SingleByteCharacter((char)'D');
	line = paper->GetAt(indexLine);
	line->Add(character);

	//종이에 '7'를 삽입한다.
	character = new SingleByteCharacter((char)'7');
	line = paper->GetAt(indexLine);
	line->Add(character);

	//문서를 만든다. 
	document = new Document();
	//문서을 저장한다. 
	document->Save(paper);
	//문서를 불러온다. 
	delete paper;
#endif
	//문서를 만든다. 
	document = new Document();

	paper = document->Load();
	
	paperString = paper->GetString();

	cout << static_cast<string>(paperString);

	return 0;
}
#endif