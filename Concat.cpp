#include "Concat.h"

void Concat::replace(string& org, int start, int length, string& dst)
{
	//org���ڿ��� start~start+length-1���� ������ dst���ڿ� ����

	
}

string Concat::concat(const string& res, const vector<string>& mis)
{
	//res: mis������� ������ ������ ���, mis: mis������� ������ ���
	
	string result = res;
	for (const string m : mis) {
		//���Ե� ���� ��ġ ����ġ
		pair<int, int> pos;

		//replace(pos.begin, pos.end)
	}

	return string();
}
