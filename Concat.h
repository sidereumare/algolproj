#pragma once
#include <string>
#include <vector>
using namespace std;
class Concat
{
	static vector<int>* ComputeSp(const string& Pattern);
public:
	static string concat(const string &res, const vector<string>& mis);
};

