#pragma once
//mismatch read모으는 역할
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

