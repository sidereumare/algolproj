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

	//bruteforce�� �̿��Ͽ� �����õ�, mismatch�߻��� misRead�� ����
	void Restore(const vector<string>& ShortLeads);
};

