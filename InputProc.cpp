#include "InputProc.h"

void InputProc::getfile(const string refFile, const string snipFile, const string readsFile)
{
	ifstream fin;
	string str;

	//레퍼런스 입력
	fin.open(refFile);
	//파일 없을 때
	if (!fin.is_open()) {
		return;
	}
	getline(fin, str);
	//테스트용 프로그램에서만
	ref = str;
	//fa파일일 때 밑에 주석 해제
	//str.reserve(60000000);
	//while (fin.peek() != EOF) {
	//	getline(fin, str);
	//	ref.append(str);
	//}
	fin.close();
	cout << refFile << "로드 완료\n";

	//snip위치 입력용 코드
	//fin.open(snipFile);
	////파일 없을 때
	//if (!fin.is_open()) {
	//	return;
	//}
	//snipPos.reserve(20000);
	//while (fin.peek() != EOF) {
	//	getline(fin, str);
	//	str = str.substr(13, 9);
	//	snipPos.push_back(stoi(str) - 1);
	//}
	//fin.close();
	//cout << snipFile << "로드 완료\n";


	//snip데이터와 fa파일 전처리
	//N으로 표기된 부분 지우고 snip데이터 지운 부분에 맞추기
	//string pn;
	//vector<int> snipProcessed;
	//pn.reserve(60000000);
	//snipProcessed.reserve(300000);
	////N의 갯수
	//int cnt = 0;
	//int j = 0;
	//for (int i = 0; i < ref.size(); i++) {
	//	if (ref[i] != 'N') {
	//		pn.push_back(ref[i]);
	//		//스닙 처리
	//		if (j < snipPos.size() && snipPos[j] == i) {				
	//			snipProcessed.push_back(i - cnt);
	//			j++;
	//			//중복될 경우 j++
	//			while (j < snipPos.size() - 1 && snipPos[j] == snipPos[j + 1])j++;
	//		}
	//	}
	//	else {
	//		cnt++;
	//	}
	//}
	//ref = pn;
	//snipPos = snipProcessed;
	//cout << "N삭제 완료\n";


	//reads파일 로드 완료
	fin.open(readsFile);
	//파일 없을 때
	if (!fin.is_open()) {
		return;
	}
	ShortReads.reserve(100000000);
	while (fin.peek() != EOF) {
		getline(fin, str);
		ShortReads.push_back(str);
	}
	fin.close();
	cout << readsFile << "로드 완료\n";

	//목표 파일
	//fin.open("modifiedSeq.txt");
	////파일 없을 때
	//if (!fin.is_open()) {
	//	return;
	//}
	//fin >> modifiedSeq;
	//fin.close();
}

//테스트 시퀀스와 랜덤한 리드 생성
//n:리드 갯수, k:리드 길이
void InputProc::makeRandomReads(int n, int k, random_device& rng)
{
	ifstream fin;
	string str;

	uniform_int_distribution<int> rngm(0, 1);
	string modify = ref;
	//일반적인 변이 추가
	
	for (auto& i : snipPos) {
		if (i >= modify.length()) {
			break;
		}
		if (rngm(rng) == 1) {
			//reference dna와 차이를 만들기위해
			//A와 T를 서로 바꾸고, C와 G를 서로 바꿉니다.
			if (modify[i] == 'A') {
				modify[i] = 'T';
			}
			else if (modify[i] == 'T') {
				modify[i] = 'A';
			}
			else if (modify[i] == 'C') {
				modify[i] = 'G';
			}
			else {
				modify[i] = 'C';
			}
		}
	}

	int m_cnt = ((double)ref.length() * 0.037) / (double)3 / (double)40;
	if (m_cnt < 10) {
		m_cnt = 10;
	}

	//변이 크기
	uniform_int_distribution<int> rng_size(30, 50);
	//변이 위치
	uniform_int_distribution<int> rng_pos(1000, ref.length() - 1000);
	//변이 갯수
	uniform_int_distribution<int> rng_num(m_cnt - 10, m_cnt + 10);

	//reverse
	int num = rng_num(rng);
	for (int i = 0; i < num; i < i++) {
		int pos = rng_pos(rng);
		reverse(modify.begin() + pos, modify.begin() + pos + rng_size(rng));
	}

	////insertion
	char ch[4] = { 'A', 'T', 'C', 'G' };
	uniform_int_distribution<int> rand_gene(0, 3);
	num = rng_num(rng);
	for (int i = 0; i < num; i++) {
		string insert_seq = "";
		int make_size = rng_size(rng);
		for (int i = 0; i < make_size; i++) {
			insert_seq.push_back(ch[rand_gene(rng)]);
		}
		int pos = rng_pos(rng);
		modify.insert(pos, insert_seq);
	}

	//deletion
	num = rng_num(rng);
	for (int i = 0; i < num; i++) {
		int pos = rng_pos(rng);
		modify.erase(pos, rng_size(rng));
	}

	modifiedSeq = modify;
	ofstream fout("modifiedSeq.txt");
	fout << modify;
	fout.close();


	ShortReads.clear();
	ShortReads.reserve(100000000);

	uniform_int_distribution<int> rngi(0, modify.length() - k);
	fout.open("ShortRead.txt");
	set<int> st;
	//임의의 위치에서 k 길이의 short read n개생성
	for (int i = 0; i < n; i++) {
		//이미 생성한 위치에 또 생성하지 않도록 set에 원소 추가 불가능할때까지
		//insert반복
		//pair<set<int>::iterator, bool> chk;
		//do {
		//	chk = st.insert(rngi(rng));
		//} while (!chk.second);

		string s = "";
		s = modify.substr(rngi(rng), k);
		
		fout << s + '\n';
		ShortReads.push_back(s);
	}
	fout.close();
}

