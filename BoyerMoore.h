#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class BoyerMoore
{

public:
	vector<string> misRead;
	string restore;

	//BoyerMoore�� �̿��Ͽ� �����õ�, mismatch�߻��� misRead�� ����
	void restore(vector<string> &ShortLeads, string &ref, vector<int> &snipPos);
};

