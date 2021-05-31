#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Benchmark
{
public:
	vector<string> misRead;
	string restore;

	//bruteforce를 이용하여 복원시도, mismatch발생시 misRead로 저장
	void Restore(const vector<string>& ShortLeads);
};

