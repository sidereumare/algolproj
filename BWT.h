#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class BWT
{
public:
	vector<string> misRead;
	string restore;
	string bwt;

	//BWT를 이용하여 복원시도, mismatch발생시 misRead로 저장
	void restore(vector<string>& ShortLeads, string& ref, vector<int>& snipPos);
	void makeBWT(string& ref);
};

