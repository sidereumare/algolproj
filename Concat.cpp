#include "Concat.h"

void Concat::replace(string& org, int start, int length, const string& dst)
{
	//org���ڿ��� start~start+length-1���� ������ start��ġ���� dst���ڿ� ����
	org.erase(start, length);
	org.insert(start, dst);
}

string Concat::concat(const string& res, const vector<string>& mis)
{
	//res: mis������� ������ ������ ���, mis: mis������� ������ ���
	
	string result = res;
	for (const string m : mis) {
		//���Ե� ���� ��ġ ����ġ
		pair<int, int> pos;

		//��ġ ã��

		//...������ �κ�

		//

		replace(result, pos.first, pos.second - pos.first + 1, m);
	}

	return string();
}
