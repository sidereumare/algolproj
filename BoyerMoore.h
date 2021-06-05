#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class BoyerMoore
{

public:
	vector<string> misRead;
	string restore;

	//BoyerMoore�� �̿��Ͽ� �����õ�, mismatch�߻��� misRead�� ����
	void Restore(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos);

	// ���Ͽ��� �����ϴ� ���ڰ� ���°���� ���������� �߻��ϴ��� �˾Ƴ� �뵵
	void badCharHeuristic(const string pattern, const int size, int* badchar);

	// ���̻簡 ��ġ�ϴ� ���� ��� ��ġ�ϴ��� ���� �뵵
	void make_gs_table(const string pattern, int* skip_tb);
};

