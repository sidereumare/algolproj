#include "Benchmark.h"

void Benchmark::RestoreBrute(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos) {
	/* 벤치마크 알고리즘 - 기본적인 Brute Force Alogrithm */

	//패턴의 길이 
	int k = ShortLeads[0].size();

	//ShortRead의 개수
	int n = ShortLeads.size();

	//reference 의 사이즈
	int m = ref.size();

	//복원할 dna를 일단 'N'으로 초기화
	restore = "";
	restore.resize(m, 'N'); // 

	//허용할 mismatch 최대 갯수
	int miss_upper = 3;

	set<int> alreadyfound; // 탐색된 위치인가..?


	//mismatch 발생시 misRead로 저장 
	string misRead(ref.length(), 'N');


	for (int i = 0; i < n; i++) {
		//100개 마다 체크..?
		/*if (i % 1000 == 0) {
			cout << i << "개 read 완료\n";
		}*/

		for (int j = 0; j < m - k + 1; j++) {
			//mismatch체크
			int mis = 0;
			bool chk = true;
			for (int l = 0; l < k; l++) { // 패턴의 길이 보다 작을 때
				if (ref[j + l] != ShortLeads[i][l]) { // reference의 시작위치 j에 l을 더한 것과, shortLeads
					mis++; // 다르면 mis ++
					misRead.push_back(ShortLeads[i][l]);
				}
				if (mis > miss_upper) { // 해당 반복문에서 mis의 개수가 허용선을 넘을 경우
					chk = false;
					break;
				}
			}

			//mis<miss_upper일 때
			//restore 배열 업데이트
			if (chk && alreadyfound.insert(j).second) {
				for (int l = 0; l < k; l++) {
					restore[j + l] = ShortLeads[i][l];
				}
			}
		}
	}
}

void Benchmark::RestoreKMP(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos) {
	/* 벤치마크 알고리즘 - 기본적인 KMP Alogrithm */

	//패턴의 길이 
	int k = ShortLeads[0].size();

	//ShortRead의 개수
	int n = ShortLeads.size();

	//reference 의 사이즈
	int m = ref.size();

	//복원할 dna를 일단 'N'으로 초기화
	restore = "";
	restore.resize(m, 'N'); // 

	//허용할 mismatch 최대 갯수
	int miss_upper = 3;

	set<int> alreadyfound; // 탐색된 위치인가?

	//아무것도 찾지못한 상태의 dna
	string make(ref.length(), 'N'); // 이거 해야하나..

	//mismatch 발생시 misRead로 저장 
	string misRead(ref.length(), 'N');

	//sp테이블 
	vector<int>* sp;


	//각 shortread 한 문장씩 끝까지 반복
	for (int t = 0; t < n; t++) {

		//int j = 0; // 현재 shortLeads의 인덱스 , 즉 패턴
		//int l = 0; // reference의 인덱스
		//cout << ShortLeads[i];
		/* mis match 체크*/
		int mis = 0;
		bool chk = true;
		/*
		 의도 : 각 shortRead의 sp테이블을 계산하려함..
		*/
		chrono::system_clock::time_point start = chrono::system_clock::now();
		sp = computeSP(ShortLeads[t]); //
		/*for (auto h = sp->begin(); h != sp->end(); h++)
			cout << *h << " ";*/

			//cout << ShortLeads[i]<<endl;
		int j = 0; // 현재 ShortLeads의인덱스 
		for (int i = 0; i < m; i++) {
			while (j > 0 && ShortLeads[t].at(j) != ref.at(i))
				j = sp->at(j - 1); // 0부터 시작해서 j-1
			if (ShortLeads[t].at(j) == ref.at(i)) {
				if (j == k - 1) {
					alreadyfound.insert(i - k + 1);
					j = sp->at(j);
				}
				else {
					j++;
				}
			}
			else {
				mis++;
				misRead.push_back(ShortLeads[t][j]);
				cout << mis << "안맞아" << endl;
				if (mis > miss_upper) {
					chk = false;
					break;
				}
			}
		}

		if (chk && (alreadyfound.find(j) != alreadyfound.end())) {
			for (int l = 0; l < k; l++) {
				restore[j + l] = ShortLeads[t][l];
				cout << "restore" << endl;
			}
		}
		chrono::system_clock::time_point end = chrono::system_clock::now();
		cout << "쇼트리드와 ref 비교 \n";
		cout << chrono::duration<double>(end - start).count() << '\n';
		cout << "어디까지왔낭 t" << t << endl;

	}
}

vector<int>* Benchmark::computeSP(const string ShortLeads) { //각 shortRead의 한 문장씩..?

	int k = ShortLeads.size();  //패턴의 길이 

		//cout << k <<"short read 길이"<< endl;
	vector<int>* sp = new vector<int>(k, 0); // vector 컨테이너 크기, 각 원소에 할당할 값
	//prefix와 suffix 테이블 만들기

	int j = 0;
	for (int i = 1; i < ShortLeads.length(); i++) {
		while (j > 0 && ShortLeads[j] != ShortLeads[i]) j = sp->at(j - 1);
		if (ShortLeads[i] == ShortLeads[j]) {
			j++;
			sp->at(i) = j;
		}
	}
	return sp;

}
//void Benchmark::RestoreKMP(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos) {
//	/* 벤치마크 알고리즘 - 기본적인 KMP Alogrithm */
//
//	//패턴의 길이 
//	int k = ShortLeads[0].size();
//
//	//ShortRead의 개수
//	int n = ShortLeads.size();
//
//	//reference 의 사이즈
//	int m = ref.size();
//
//	//복원할 dna를 일단 'N'으로 초기화
//	restore = "";
//	restore.resize(m, 'N'); // 
//
//	//허용할 mismatch 최대 갯수
//	int miss_upper = 3;
//
//	set<int> alreadyfound; // 탐색된 위치인가?
//
//	//아무것도 찾지못한 상태의 dna
//	string make(ref.length(), 'N'); // 이거 해야하나..
//
//	//mismatch 발생시 misRead로 저장 
//	string misRead(ref.length(), 'N');
//
//	//sp테이블 
//	int* sp = new int[k];
//
//
//
//	//각 shortread 한 문장씩 끝까지 반복
//	for (int i = 0; i < n; i++) {
//
//		int j = 0; // 현재 shortLeads의 인덱스 , 즉 패턴
//		int l = 0; // reference의 인덱스
//
//		/* mis match 체크*/
//		int mis = 0;
//		bool chk = true;
//		/*
//		 의도 : 각 shortRead의 sp테이블을 계산하려함..
//		*/
//		sp = computeSP(ShortLeads[i]); //
//		while (l < m) { // l<ref의 길이보다 작을 때 
//
//			if (ShortLeads[i][j] == ref[l]) {
//				j++;
//				l++;
//			}
//			if (j == k) { // 패턴 길이와 같다면
//				//cout << "Found ShortLeads[i][j] pattern here %d \n"<< i-j; //이거던가..
//				j = sp[j - 1];
//			}
//			/* 여기서 부터 추가 고민 필요함..*/
//			else if (l < m && ShortLeads[i][j] != ref[l]) { //
//				//sp[0..sp[j-1]]와 안맞을 때,  
//				mis++;
//				misRead.push_back(ShortLeads[i][l]);
//				if (mis > miss_upper) { // 해당 반복문에서 mis의 개수가 허용선을 넘을 경우
//					chk = false;
//					break;
//				}
//
//				if (j != 0)
//					j = sp[j - 1];
//				else {
//					if (mis)
//						i = i + 1;
//				}
//
//			}
//		}
//		//mis<miss_upper일 때
//		//restore 배열 업데이트
//		if (chk && alreadyfound.insert(j).second) {
//			for (int l = 0; l < k; l++) {
//				restore[j + l] = ShortLeads[i][l];
//			}
//		}
//
//	}
//}
