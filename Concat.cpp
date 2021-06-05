#include "Concat.h"

vector<int>* Concat::ComputeSp(const string& Pattern) {
	//입력: Pattern 패턴 스트링
	//출력: 최대 접두부 테이블
	vector<int>* sp = new vector<int>(Pattern.length(), 0);
	int j = 0;
	for (int i = 1; i < Pattern.length(); i++) {
		while (j > 0 && Pattern[j] != Pattern[i]) j = sp->at(j - 1);
		if (Pattern[i] == Pattern[j]){
			j++;
			sp->at(i) = j;
		}
	}
	return sp;
}

void Concat::analyze(const vector<string>& mis)
{
	//sp계산
	for (int i = 0; i < res_.size(); i++) {
		res_sp.push_back(ComputeSp(res_[i]));
	}

	match_data.assign(mis.size(), pair<vector<pair<int, int> >, int >());
	//겹치는 부분 검색후 표시

	auto func = [this, &mis](int start) {
		for (int i = start; i < mis.size(); i+=10) {
			match_data[i].second = i;

			//종류, 시작 위치
			pair<int, int> pos;

			int n_p = 0;
			for (int j = 0; j < res_.size(); j++) {
				int m_p = 0;
				if (match_data[i].first.empty()) {
					n_p = 0;
				}

				bool found = false;
				//kmp를 이용해 mis[i]안에 res_[j]있는지 확인
				while (n_p < mis[i].size()) {
					while (m_p > 0 && mis[i][n_p] != res_[j][m_p]) {
						m_p = (*res_sp[j])[m_p - 1];
					}
					if (mis[i][n_p] == res_[j][m_p]) {
						if (j == res_[j].size() - 1) {
							pos.first = j;
							pos.second = n_p - res_[j].size() + 1;
							found = true;
							break;
						}
						else {
							j++;
						}
					}
					n_p++;
				}

				//있으면 기록 없으면 다음, 없는데 이전 데이터 있는경우 중단
				if (found) {
					_mux.lock();
					match_data[i].first.push_back(pos);
					_mux.unlock();
				}
				else if (!found && !match_data[i].first.empty()) {
					break;
				}
			}
		}
	};

	vector<thread> t;
	for (int i = 0; i < 10; i++) {
		t.push_back(thread(func, i));
	}
	for (auto& e : t) {
		e.join();
	}
}

string Concat::concat(const string& res, vector<string>& mis)
{
	//res: mis리드들을 제외한 복원된 결과, mis: mis리드들을 연결한 결과
	
	
	//res분해
	int i = 0;
	string s = "";
	while (i < res.length()) {
		if (res[i] != 'N') {
			s.push_back(res[i]);
			i++;
		}
		else {
			if (!s.empty()) {
				res_.push_back(s);
				s.clear();
			}
			i++;
		}
	}
	
	analyze(mis);
	
	//matchdata정보 정렬
	sort(match_data.begin(), match_data.end());

	//정렬된 정보를 이용해 reconstruct
	string result;
	result = mis[match_data[0].second];
	for (int i = 1; i < match_data.size(); i++) {
		if ((match_data[i - 1].first.end() - 1)->first == (match_data[i - 1].first.begin())->first) {
			auto it = match_data[i - 1].first.end() - 1;
			int pos = mis[match_data[i - 1].second].size() - it->second;
			result.replace(pos, result.size() - pos, mis[match_data[i].second]);
		}
		else {
			result += mis[match_data[i].second];
		}
	}

	return result;
}
