#pragma once
//mismatch read������ ����
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Euiler
{

public:
	vector<string> restored;
	//Euiler
	
	void Restore(const vector<string> &misRead);
	void find_pos(const string& restored, const vector<string>& mis);

};

