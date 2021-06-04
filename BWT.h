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

	//BWT�� �̿��Ͽ� �����õ�, mismatch�߻��� misRead�� ����
	void Restore(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos);
	void makeBWT(const string& ref);
};

