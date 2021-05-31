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

	//BWT�� �̿��Ͽ� �����õ�, mismatch�߻��� misRead�� ����
	void restore(vector<string>& ShortLeads, string& ref, vector<int>& snipPos);
	void makeBWT(string& ref);
};

