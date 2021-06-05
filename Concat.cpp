#include "Concat.h"

vector<int>* Concat::ComputeSp(const string& Pattern) {
	//입력: Pattern 패턴 스트링
	//출력: 최대 접두부 테이블
	vector<int>* sp = new vector<int>(Pattern.length(), 0);
	int j = 0;
	for (int i = 1; i < Pattern.length(); i++) {
		while (j > 0 && Pattern[j] != Pattern[i]) j = sp->at(j - 1);
		if (Pattern[i] == Pattern[j])j++;
		sp->at(i) = j;
	}
	return sp;
}

string Concat::concat(const string& res, const vector<string>& mis)
{
	//res: mis리드들을 제외한 복원된 결과, mis: mis리드들을 연결한 결과
	
	string result = res;

	//mis리드를 사용했는지 표시
	vector<bool> already_visit(mis.size(), false);

	//삽입될 시작 위치, 길이
	pair<int, int> pos(0, 0);
	string str = "";
	for (int i = 0; i < mis.size(); i++) {
		if (already_visit[i]) {
			continue;
		}

		//최대 접두부 테이블 생성
		vector<int>* suffix = ComputeSp(mis[i]);

		int npos = result.find_first_of('N');
		int start = npos - mis[i].length();
		if (start < 0) {
			start = 0;
		}

		bool chk = false;
		int k = 0;
		for (int j = start; j < npos + mis[i].length(); j++) {
			while (k > 0 && (mis[i][k] != result[j])) {
				if (result[j] == 'N') {
					break;
				}
				k = (*suffix)[k - 1];
			}
			if (k == 0) {
				pos.first = j;
			}
			if (result[j] == mis[i][k]) {
				k++;
				if (k == mis[i].length()-1) {
					already_visit[i] = true;
					chk = true;
					pos.second = k+1;
					break;
				}
			}

			//N이 안나올때 까지 j옮김
			else if (result[j] == 'N') {
				int cnt_n = 0;
				while (result[j+cnt_n] == 'N') {
					cnt_n++;
				}
				j += cnt_n;
				for (int l = 0; l <= cnt_n; l++) {
					int len = mis[i].length() - (k + l);
					string s1 = mis[i].substr(k + l, len);
					string s2 = result.substr(j, len);
					if (s1==s2) {
						already_visit[i] = true;
						chk = true;
						pos.second = j+len;
						break;
					}
				}
				if (chk) {
					break;
				}
			}
		}

		if (chk) {
			str = mis[i];
			result.replace(pos.first, pos.second - pos.first, str);
		}
	}

	
	return result;
}
