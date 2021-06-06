#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <chrono>

using namespace std;
class Benchmark
{
public:
	vector<string> misRead;
	string restore;

	//bruteforce�� �̿��Ͽ� �����õ�, mismatch�߻��� misRead�� ����
	void RestoreBrute(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos);

	//KMP�� �̿��Ͽ� �����õ�, mismatch�߻��� misRead�� ����
	void RestoreKMP(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos);

	//ComputeSP()
	vector<int>* computeSP(const string& ShortLead);
};

