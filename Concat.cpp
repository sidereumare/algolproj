#include "Concat.h"

vector<int>* Concat::ComputeSp(const string& Pattern) {
	//�Է�: Pattern ���� ��Ʈ��
	//���: �ִ� ���κ� ���̺�
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
	//sp���
	for (int i = 0; i < res_.size(); i++) {
		res_sp.push_back(ComputeSp(res_[i]));
	}

	match_data.assign(mis.size(), pair<vector<pair<int, int> >, int >());
	//��ġ�� �κ� �˻��� ǥ��

	auto func = [this, &mis](int start) {
		for (int i = start; i < mis.size(); i+=10) {
			match_data[i].second = i;

			//����, ���� ��ġ
			pair<int, int> pos;

			int n_p = 0;
			for (int j = 0; j < res_.size(); j++) {
				int m_p = 0;
				if (match_data[i].first.empty()) {
					n_p = 0;
				}

				bool found = false;
				//kmp�� �̿��� mis[i]�ȿ� res_[j]�ִ��� Ȯ��
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

				//������ ��� ������ ����, ���µ� ���� ������ �ִ°�� �ߴ�
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
	//res: mis������� ������ ������ ���, mis: mis������� ������ ���
	
	
	//res����
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
	
	//matchdata���� ����
	sort(match_data.begin(), match_data.end());

	//���ĵ� ������ �̿��� reconstruct
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
