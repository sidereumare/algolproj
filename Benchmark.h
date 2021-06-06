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

	//bruteforce를 이용하여 복원시도, mismatch발생시 misRead로 저장
	void RestoreBrute(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos);

	//KMP를 이용하여 복원시도, mismatch발생시 misRead로 저장
	void RestoreKMP(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos);

	//ComputeSP()
	vector<int>* computeSP(const string& ShortLead);
};

