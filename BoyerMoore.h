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
	void Restore(const vector<string> &ShortLeads, const string &ref, const vector<int> &snipPos);
};

