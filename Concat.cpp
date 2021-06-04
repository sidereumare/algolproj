#include "Concat.h"

void Concat::replace(string& org, int start, int length, const string& dst)
{
	//org문자열에 start~start+length-1까지 삭제후 start위치부터 dst문자열 삽입
	org.erase(start, length);
	org.insert(start, dst);
}

string Concat::concat(const string& res, const vector<string>& mis)
{
	//res: mis리드들을 제외한 복원된 결과, mis: mis리드들을 연결한 결과
	
	string result = res;
	for (const string m : mis) {
		//삽입될 시작 위치 끝위치
		pair<int, int> pos;

		//위치 찾기

		//...구현할 부분

		//

		replace(result, pos.first, pos.second - pos.first + 1, m);
	}

	return string();
}
