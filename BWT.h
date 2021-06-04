#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
class BWT
{
public:
	vector<string> misRead;
	string restore;
	string bwt;

	//BWT를 이용하여 복원시도, mismatch발생시 misRead로 저장
	void Restore(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos);
	void makeBWT(const string& ref);
};

