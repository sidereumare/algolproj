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

	//���Ͽ��� ���۷��� ������ġ shortReads������ �ε�
	void getfile(string refFile, string readsFile);	
};
