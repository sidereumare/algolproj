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

	
	//레퍼런스, 스닙, shortReads데이터 로드, modifiedSeq존재하면 로드
	void getfile(const string refFile, const string snipFile, const string readsFile);

	//스닙에서 랜덤한 변이가 발생한 예제
	void makeRandomReads(int n, int k, random_device &rng);
};
