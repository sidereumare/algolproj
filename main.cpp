#include <iostream>
#include <chrono>
#include "InputProc.h"
#include "BWT.h"
#include "BoyerMoore.h"
#include "Euiler.h"
#include "Concat.h"
#include "Benchmark.h"

using namespace std;

//최소 편집거리를 이용하여 성능 평가
//시간복잡도 O(mn), 공간복잡도 O(m)
//int calcDifference(const string& org, const string& dif) {
//	int m = org.length() + 1;
//	int n = dif.length() + 1;
//
//	int* arr = new int[m];
//	for (int i = 0; i < m; i++) {
//		arr[i] = i;
//	}
//
//	for (int i = 1; i < n; i++) {
//		int before = arr[0];
//		arr[0] = i;
//		for (int j = 1; j < m; j++) {
//			int cost = 0;
//			if (org[j - 1] != dif[i - 1]) {
//				cost = 1;
//			}
//			int temp = arr[j];
//			arr[j] = min(arr[j - 1] + 1, min(arr[j] + 1, before + cost));
//			before = temp;
//		}
//	}
//	int rst = arr[m - 1];
//	delete[]arr;
//	return rst;
//}

string bwt(InputProc& input, int lmer) {
	//1-1 첫번째과정
	//BWT알고리즘 활용
	chrono::system_clock::time_point bwt_start = chrono::system_clock::now();
	BWT bwt;
	bwt.Restore(input.ShortReads, input.ref, input.snipPos);
	chrono::system_clock::time_point bwt_end = chrono::system_clock::now();
	cout << "BWT완료\n";
	//cout << chrono::duration<double>(bwt_end - bwt_start).count() << '\n';

	//2-1
	//euiler로 BWT로 만들어진 misRead를 처리하여 sequence를 복원
	chrono::system_clock::time_point euiler_start = chrono::system_clock::now();
	Euiler bwt_euiler;
	vector<string>* restored_mis;
	restored_mis = bwt_euiler.Restore(bwt.misRead, lmer);
	chrono::system_clock::time_point euiler_end = chrono::system_clock::now();
	cout << "euiler완료\n";
	//cout << chrono::duration<double>(euiler_end - euiler_start).count() << '\n';

	//3-1 복원한 sequence를 1-2단계에서 복원한 sequence와 concat시킵니다.
	chrono::system_clock::time_point concat_start = chrono::system_clock::now();
	Concat con;
	string result = con.concat(bwt.restore, *restored_mis);
	chrono::system_clock::time_point concat_end = chrono::system_clock::now();
	cout << "Construct완료\n";
	cout << chrono::duration<double>(concat_end - bwt_start).count() << "초\n";


	ofstream fout("1-1reconstructed.txt");
	fout << result;
	fout.close();

	return "1-1reconstructed.txt";
}

string bm(InputProc& input, int lmer) {
	////1-2
	//Boyer-Moore Algorithm 활용
	chrono::system_clock::time_point boyer_start = chrono::system_clock::now();
	BoyerMoore bm;
	bm.Restore(input.ShortReads, input.ref, input.snipPos);
	chrono::system_clock::time_point boyer_end = chrono::system_clock::now();
	cout << "Boyer-Moore완료\n";
	//cout << chrono::duration<double>(boyer_end - boyer_start).count() << '\n';

	//2-2
	//euiler로 Boyer-Moore 로 만들어진 misRead를 처리하여 sequence를 복원
	//chrono::system_clock::time_point euiler_start1 = chrono::system_clock::now();
	Euiler bm_euiler;
	vector<string>* restored_mis1;
	restored_mis1 = bm_euiler.Restore(bm.misRead, lmer);
	chrono::system_clock::time_point euiler_end1 = chrono::system_clock::now();
	cout << "Euiler완료\n";
	//cout << chrono::duration<double>(euiler_end1 - euiler_start1).count() << '\n';

	//3-2 복원한 sequence를 1-2단계에서 복원한 sequence와 concat시킵니다.
	chrono::system_clock::time_point concat_start1 = chrono::system_clock::now();
	Concat con1;
	string result1 = con1.concat(bm.restore, *restored_mis1);
	chrono::system_clock::time_point concat_end1 = chrono::system_clock::now();
	cout << "Construct완료\n";
	cout << chrono::duration<double>(concat_end1 - boyer_start).count() << "초\n";

	ofstream fout("1-2reconstructed.txt");
	fout << result1;
	fout.close();

	return "1-2reconstructed.txt";
}

string benchKMP(InputProc& input) {
	//성능 벤치마크용	
	Benchmark bench;
	//벤치마크 시작
	chrono::system_clock::time_point bench_start = chrono::system_clock::now();
	bench.RestoreKMP(input.ShortReads, input.ref, input.snipPos);
	chrono::system_clock::time_point bench_end = chrono::system_clock::now();
	cout << "kmp종료\n";
	cout << chrono::duration<double>(bench_end - bench_start).count() << "초\n";
	ofstream fout("kmpreconstructed.txt");
	fout << bench.restore;
	fout.close();

	return "kmpreconstructed.txt";
}

string benchBrute(InputProc& input) {
	Benchmark bench1;
	cout << "bruteforce 시작\n";
	chrono::system_clock::time_point bench_start1 = chrono::system_clock::now();
	bench1.RestoreBrute(input.ShortReads, input.ref, input.snipPos);
	chrono::system_clock::time_point bench_end1 = chrono::system_clock::now();
	cout << "bruteforce완료\n";
	cout << chrono::duration<double>(bench_end1 - bench_start1).count() << "초\n";
	ofstream fout("brutereconstructed.txt");
	fout << bench1.restore;
	fout.close();

	return "brutereconstructed.txt";
}

random_device rng;
int main() {
	
	////30000000
	//InputProc input;
	//input.getfile("NC_000022.11[1..50818468].fa", "Clinical  dbSNP b154 v2.BED", "ShortRead.txt");
	////cout << input.ref.size();
	////return 0;
	////이미 있는데 make호출시 shortreads.txt와 modifiedseq.txt, inputProc의 내용이 변경됨
	//cout << "사용할 레퍼런스의 길이를 입력해 주세요\n";
	//int ref_len;
	//cin >> ref_len;
	//input.ref = input.ref.substr(0, ref_len);
	//input.makeRandomReads(ref_len/2, 100, rng);
	//cout << "데이터 생성완료" << '\n';
	
	InputProc input;
	cout << "데이터의 경로를 입력해주세요: ";
	string datapath; //데이터 경로
	cin >> datapath;
	input.getfile(datapath + "\\ref.txt", "", datapath + "\\shortread.txt");

	
	while (true) {
		cout << "테스트할 알고리즘을 선택해 주세요\n";
		cout << "1:BWT를 이용한 알고리즘, 2:BM를 이용한 알고리즘\n";
		cout << "3:벤치마크용 kmp알고리즘, 4:벤치마크용 Bruteforce알고리즘";
		cout << "종료:1~4이외의 입력\n";
		
		int test;//테스트할 알고리즘 번호
		string rstpath;//결과 경로
		
		cin >> test;
		
		//bwt
		if (test == 1) {
			int lmer;
			cout << "현재 shortread길이 " << input.ShortReads[0].length() << '\n';
			cout << "lmer값을 입력해 주세요(3~shortread길이 - 3)\n";
			cin >> lmer;
			if (lmer > input.ShortReads[0].length() - 3 || lmer < 3) {
				break;
			}
			rstpath = bwt(input, lmer);
		}
		//BM
		else if (test == 2) {
			int lmer;
			cout << "현재 shortread길이 " << input.ShortReads[0].length() << '\n';
			cout << "lmer값을 입력해 주세요(3~shortread길이 - 3)\n";
			cin >> lmer;
			if (lmer > input.ShortReads[0].length() - 3 || lmer < 3) {
				break;
			}
			rstpath = bm(input, lmer);
		}
		//KMP
		else if (test == 3) {
			rstpath = benchKMP(input);
		}
		//Bruteforce
		else if (test == 4) {
			rstpath = benchBrute(input);
		}
		//종료
		else {
			break;
		}
		//정답율 체크
		system((".\\diff.exe " + datapath + "\\mydna.txt " + rstpath).c_str());
	}
	
	return 0;
}