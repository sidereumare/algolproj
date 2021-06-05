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

	//BoyerMoore를 이용하여 복원시도, mismatch발생시 misRead로 저장
	void Restore(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos);

	// 패턴에서 존재하는 문자가 몇번째에서 마지막으로 발생하는지 알아낼 용도
	void badCharHeuristic(const string pattern, const int size, int* badchar);

	// 접미사가 일치하는 순간 몇개가 일치하는지 세는 용도
	void make_gs_table(const string pattern, int* skip_tb);
};

