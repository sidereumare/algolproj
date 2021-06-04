#pragma once
#include <string>
#include <vector>
using namespace std;
class Concat
{
	static void replace(string& org, int start, int end, string& dst);
public:
	static string concat(const string &res, const vector<string>& mis);
};

