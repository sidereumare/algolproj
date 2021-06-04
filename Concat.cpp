#include "Concat.h"

void Concat::replace(string& org, int start, int length, string& dst)
{
	//org문자열에 start~start+length-1까지 삭제후 dst문자열 삽입

	
}

string Concat::concat(const string& res, const vector<string>& mis)
{
	//res: mis리드들을 제외한 복원된 결과, mis: mis리드들을 연결한 결과
	
	string result = res;
	for (const string m : mis) {
		//삽입될 시작 위치 끝위치
		pair<int, int> pos;

		//replace(pos.begin, pos.end)
	}

	return string();
}
