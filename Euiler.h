#pragma once
//mismatch read������ ����
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <map>
#include <stack>
#include <thread>
#include <mutex>

using namespace std;
class Euiler
{
	//�׷��� ���� ����
	vector<string> dict;
	//�׷���
	//���� �ε��� : ��� ���, ���� Ű:���� ���, �������� first:��ũ ��, second:�湮üũ��
	vector<map<int, pair<int, bool> > > graph;
	//�� ������ ��
	int edgecnt = 0;
	vector<int> ind;

	//���Ϸ� �׷����� ���� ������ ���ڿ���
	vector<string> EuilerRst;
	
	mutex _mux;

	int findgraph(string find);
	void makegraph(const vector<string>& misRead, int l);
	void makepath(int current, vector<int>& st, vector<vector<int> >& ans);
public:
	vector<string> restored;
	//Euiler
	
	vector<string>* Restore(const vector<string> &misRead, int l);
};

