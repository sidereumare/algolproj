#include "Euiler.h"

int Euiler::findgraph(string find)
{
	//�Է�: dict:���ڿ� �迭, find:ã�� ���ڿ�
	//���: ��ã�� �� -1, ã���� �迭���� ��ġ�� ����
	for (int i = 0; i < dict.size(); i++) {
		if (dict[i] == find) {
			return i;
		}
	}
	return -1;
}

//l:31~127
//https://www.youtube.com/watch?v=OY9Q_rUCGDw
void Euiler::makegraph(const vector<string>& misRead, int l)
{
	//�Է�: misRead:�׷��� ���� Read, l:l-merũ��
	//�׷��� ����� �޼ҵ�

	int readLength = misRead[0].size();
	//�����߻��� ���
	assert(1 <= l && l < readLength);

	//vector<string> lmers;
	//vector<int> ind;

	//�׷��� �����
	//��� read���� lmer�� ����
	int dict_cnt = 0;
	for (auto s : misRead) {
		for (int i = 0; i < readLength - l; i++) {
			string sub1, sub2;
			sub1 = s.substr(i, l);
			sub2 = s.substr(i + 1, l);
			//int s1, s2;
			//ù��° substr�� ��ġ ã��
			//s1 = findgraph(sub1);
			auto s1 = dict_.find(sub1);
			if (s1 == dict_.end()) {
				dict.push_back(sub1);
				s1 = dict_.insert(make_pair(sub1, dict_cnt++)).first;
				graph.push_back(map <int, pair<int, bool> >());
				//s1 = dict.size() - 1;
			}
			//�ι�° substr�� ��ġ ã��
			//s2 = findgraph(sub2);
			auto s2 = dict_.find(sub2);
			if (s2 == dict_.end()) {
				dict.push_back(sub2);
				s2 = dict_.insert(make_pair(sub2, dict_cnt++)).first;
				graph.push_back(map<int, pair<int, bool> >());
				//s2 = dict.size() - 1;
			}
			//s1->s2�� ���� ��� ����
			auto ret = graph[s1->second].insert( make_pair(s2->second, make_pair(1, true)) );
			if (!ret.second) {
				ret.first->second.first++;
			}
			edgecnt++;
		}
	}

	ind.assign(graph.size(), 0);
	//indegree���
	for (int i = 0; i < graph.size(); i++) {
		for (auto t : graph[i]) {
			ind[t.first]++;
		}
	}

}

void Euiler::makepath(int current, vector<int> &st, vector<vector<int> > &ans)
{
	//current:���� ����� ��ġ, st:��θ� �����ϰ� �ִ� ����
	// ans: ��θ� ����ϱ� ���� ����
	// 
	//���ÿ� ������ �߰�
	st.push_back(current);
	
	//������ ������� üũ�ϴ� ����
	bool chk = true;
	//��� ���� �湮
	for (auto& c : graph[current]) {
		if (c.second.second) {
			//�湮üũ�� false�� ����
			c.second.second = false;
			//���� ��� �湮
			makepath(c.first, st, ans);

			//üũ ����
			c.second.second = true;

			//������ ��尡 �ƴ϶�� üũ
			chk = false;
			break;
		}
	}

	//��������忡�� ��� ����
	if (chk) {
		_mux.lock();
		ans.push_back(st);
		_mux.unlock();
	}
	//���ؿ��� ����
	st.pop_back();
}

vector<string>* Euiler::Restore(const vector<string>& misRead, int l)
{
	//�Է�: misRead:match���� ���� reads, l:l-mer�� ����

	//l-mer�� �̿��Ͽ� de bruijn graph����
	makegraph(misRead, l);

	//indegree�񱳸� ����
	//start ��ġ ã��
	vector<int> startNodes;
	for (int i = 0; i < graph.size(); i++) {
		if (graph[i].size() > ind[i]) {
			startNodes.push_back(i);
		}
	}

	vector<vector<int> > ans;
	auto func = [this, &startNodes, &ans](int start) {
		for (int i = start; i < startNodes.size(); i+=10) {
			vector<int> st;
			makepath(startNodes[i], st, ans);
		}
	};

	vector<thread> t;
	for (int i = 0; i < 10; i++) {
		t.push_back(thread(func, i));
	}
	for (auto& e : t) {
		e.join();
	}

	vector<string>* res = new vector<string>();

	//��� ��� ���
	string str;
	for (int i = 0; i < ans.size(); i++) {
		str = dict[ans[i][0]];
		for (int j = 1; j < ans[i].size(); j++) {
			str.push_back(dict[ans[i][j]][dict[ans[i][j]].length() - 1]);
		}
		res->push_back(str);
	}

	return res;
}


