#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <mutex>
using namespace std;
class BWT
{
	void makeBWT(const string& ref);
	mutex _mux;
	int search(const string& target, const vector<int>& snipPos);
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
};

