#pragma once
//mismatch read모으는 역할
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
	//그래프 원소 관리
	vector<string> dict;
	//그래프
	//벡터 인덱스 : 출발 노드, 맵의 키:도착 노드, 데이터의 first:링크 수, second:방문체크용
	vector<map<int, pair<int, bool> > > graph;
	//총 엣지의 수
	int edgecnt = 0;
	vector<int> ind;

	//오일러 그래프를 통해 복원한 문자열들
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

