#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
class BWT
{
	int search(const string& target);
public:
	vector<string> misRead;
	string restore;
	string bwt;
	string first;
	
	//���� ��ġ
	vector<int> originpos;
	vector<int> postofirst;
	//ACGT������***
	int posstart[4] = { -1,-1,-1,-1 };

	//BWT�� �̿��Ͽ� �����õ�, mismatch�߻��� misRead�� ����
	void Restore(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos);
	void makeBWT(const string& ref);
};

