#include "Euiler.h"

int Euiler::findgraph(string find)
{
	//입력: dict:문자열 배열, find:찾을 문자열
	//출력: 못찾을 시 -1, 찾으면 배열에서 위치를 리턴
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
	//입력: misRead:그래프 만들 Read, l:l-mer크기
	//그래프 만드는 메소드

	int readLength = misRead[0].size();
	//오류발생시 출력
	assert(1 <= l && l < readLength);

	//vector<string> lmers;
	//vector<int> ind;

	//그래프 만들기
	//모든 read들을 lmer로 분할
	for (auto s : misRead) {
		for (int i = 0; i < readLength - l; i++) {
			string sub1, sub2;
			sub1 = s.substr(i, l);
			sub2 = s.substr(i + 1, l);
			int s1, s2;
			//첫번째 substr의 위치 찾기
			s1 = findgraph(sub1);
			if (s1 == -1) {
				dict.push_back(sub1);
				graph.push_back(map <int, pair<int, bool> >());
				s1 = dict.size() - 1;
			}
			//두번째 substr의 위치 찾기
			s2 = findgraph(sub2);
			if (s2 == -1) {
				dict.push_back(sub2);
				graph.push_back(map<int, pair<int, bool> >());
				s2 = dict.size() - 1;
			}
			//s1->s2로 가는 경로 지정
			auto ret = graph[s1].insert( make_pair(s2, make_pair(1, true)) );
			if (!ret.second) {
				ret.first->second.first++;
			}
			edgecnt++;
		}
	}

	ind.assign(graph.size(), 0);
	//indegree계산
	for (int i = 0; i < graph.size(); i++) {
		for (auto t : graph[i]) {
			ind[t.first]++;
		}
	}

}

void Euiler::makepath(int current, vector<int> &st, vector<vector<int> > &ans)
{
	//current:현재 노드의 위치, st:경로를 유지하고 있는 스택
	// ans: 경로를 출력하기 위한 변수
	// 
	//스택에 현재노드 추가
	st.push_back(current);
	
	//마지막 노드임을 체크하는 변수
	bool chk = true;
	//모든 엣지 방문
	for (auto& c : graph[current]) {
		if (c.second.second) {
			//방문체크를 false로 변경
			c.second.second = false;
			//다음 노드 방문
			makepath(c.first, st, ans);
			//방문체크를 true로 변경
			c.second.second = true;

			//마지막 노드가 아니라고 체크
			chk = false;
		}
	}

	//마지막노드에서 경로 저장
	if (chk) {
		ans.push_back(st);
	}
	//스텍에서 제거
	st.pop_back();
}

vector<string>* Euiler::Restore(const vector<string>& misRead, int l)
{
	//입력: misRead:match되지 못한 reads, l:l-mer의 길이

	//l-mer을 이용하여 de bruijn graph생성
	makegraph(misRead, l);

	//indegree비교를 통해
	//start 위치 찾기
	vector<int> startNodes;
	for (int i = 0; i < graph.size(); i++) {
		if (graph[i].size() > ind[i]) {
			startNodes.push_back(i);
		}
	}

	vector<vector<int> > ans;
	vector<int> st;
	for (int i = 0; i < startNodes.size(); i++) {
		st.clear();
		makepath(startNodes[i], st, ans);
	}

	vector<string>* res = new vector<string>();

	//모든 경로 출력
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


