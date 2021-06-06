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
	
	//원래 위치
	vector<int> originpos;
	vector<int> postofirst;
	//ACGT순서임***
	int posstart[4] = { -1,-1,-1,-1 };

	//BWT를 이용하여 복원시도, mismatch발생시 misRead로 저장
	void Restore(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos);
};

