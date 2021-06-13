#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <mutex>
using namespace std;


class BoyerMoore
{

public:
	vector<string> misRead;
	string restore;
	mutex _mutex;

	//BoyerMoore�� �̿��Ͽ� �����õ�, mismatch�߻��� misRead�� ����
	void Restore(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos);

	// ���Ͽ��� �����ϴ� ���ڰ� ���°���� ���������� �߻��ϴ��� �˾Ƴ� �뵵
	void badCharHeuristic(const string pattern, const int size, int* badchar);

	void good_suffix_Heuristic(int* shift, int* bpos, string pattern, int m);

	void preprocess_case2(int* shift, int* bpos, string pattern, int m);

	// ���̻簡 ��ġ�ϴ� ���� ��� ��ġ�ϴ��� ���� �뵵
	//void make_gs_table(const string pattern, int* skip_tb);
};

