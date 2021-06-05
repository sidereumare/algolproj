#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
using namespace std;
class Concat
{
	vector<int>* ComputeSp(const string& Pattern);
	void analyze(const vector<string>& mis);
	vector<vector<int>* > res_sp;
	vector<string> res_;
	mutex _mux;
	//vector<pair<int,int>>res_번호와 시작위치, int:원래 위치
	vector<pair<vector<pair<int, int> >, int> > match_data;
public:
	string concat(const string &res, vector<string>& mis);
	
};

