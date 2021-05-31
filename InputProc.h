#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
class InputProc
{
public:
	vector<string> ShortReads;
	vector<int> snipPos;
	string ref;

	//파일에서 레퍼런스 스닙위치 shortReads데이터 로드
	void getfile(string refFile, string readsFile);	
};
