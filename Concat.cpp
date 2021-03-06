#include "Concat.h"

vector<int>* Concat::ComputeSp(const string& Pattern) {
	//입력: Pattern 패턴 스트링
	//출력: 최대 접두부 테이블
	vector<int>* sp = new vector<int>(Pattern.length(), 0);
	int j = 0;
	for (int i = 1; i < Pattern.length(); i++) {
		while (j > 0 && Pattern[j] != Pattern[i]) j = sp->at(j - 1);
		if (Pattern[i] == Pattern[j]) {
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
		for (int i = start; i < mis.size(); i += 10) {
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
						if (m_p == res_[j].size() - 1) {
							pos.first = j;
							pos.second = n_p - res_[j].size() + 1;
							found = true;
							break;
						}
						else {
							m_p++;
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
	string result = "";

	int before = -1;
	//없는 부분 띄어넘기
	for (int i = 0; i < match_data.size(); i++) {
		if (match_data[i].first.empty()) {
			before = i;
		}
		else {
			break;
		}
	}

	if (before + 1 == match_data.size()) {
		for (int i = 0; i < res_.size(); i++) {
			result += res_[i];
		}
		return result;
	}

	//첫번째로 등장하는 수가 0이 아니면 그 수-1 까지 문자열 추가
	before += 1;
	int chk = match_data[before].first.begin()->first;
	for (int i = 0; i < chk; i++) {
		result += res_[i];
	}

	
	//체크하면서 사이에 낀 부분 체크
	for (int i = chk; i < res_.size(); i++) {
		//현재 상태에 match_data가 있는지 체크
		bool chk_isin = false;
		int pos = 0;
		if (before < match_data.size()) {
			for (auto& a : match_data[before].first) {
				if (a.first == i) {
					chk_isin = true;
					pos = a.second;
					i = (match_data[before].first.end() - 1)->first;
				}
			}
		}
		//한번도 등장 안하면 추가
		if (!chk_isin) {
			result += res_[i];
		}
	}
	//첫번째
	//result += mis[match_data[before + 1].second];
	//for (int i = before + 2; i < match_data.size(); i++) {
	//	auto it1 = match_data[i - 1].first.end() - 1;
	//	auto it2 = match_data[i].first.begin();
	//	//일반적인 경우
	//	if (it1->first == it2->first) {
	//		int pos = mis[match_data[i - 1].second].size() - it1->second;
	//		result.replace(pos, result.size() - pos, mis[match_data[i].second]);
	//	}
	//	//중간에 값이 등장하지 않는 경우
	//	else if (it1->first < it2->first) {
	//		for (int j = it1->first + 1; j < it2->first; j++) {
	//			result += res_[j];
	//		}
	//		result += mis[match_data[i].second];
	//	}
	//	//서로 많이 겹치는 경우
	//	else {
	//		while (it1->first != it2->first && it1 != match_data[i - 1].first.begin()) {
	//			it1--;
	//		}
	//		int pos = mis[match_data[i - 1].second].size() - it1->second;
	//		result.replace(pos, result.size() - pos, mis[match_data[i].second]);
	//	}
	//}

	return result;
}
