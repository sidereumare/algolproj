#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <set>
using namespace std;


class InputProc
{
public:
	vector<string> ShortReads;
	vector<int> snipPos;
	string ref;
	string modifiedSeq;

	
	//���۷���, ����, shortReads������ �ε�, modifiedSeq�����ϸ� �ε�
	void getfile(const string refFile, const string snipFile, const string readsFile);

	//���տ��� ������ ���̰� �߻��� ����
	void makeRandomReads(int n, int k, random_device &rng);
};
