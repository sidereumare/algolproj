#include <iostream>
#include <chrono>
#include "InputProc.h"
#include "BWT.h"
#include "BoyerMoore.h"
#include "Euiler.h"
#include "Concat.h"
using namespace std;

//최소 편집거리를 이용하여 성능 평가
//시간복잡도 O(mn), 공간복잡도 O(m)
int calcDifference(const string& org, const string& dif) {
	int m = org.length() + 1;
	int n = dif.length() + 1;

	int* arr = new int[m];
	for (int i = 0; i < m; i++) {
		arr[i] = i;
	}

	for (int i = 1; i < n; i++) {
		int before = arr[0];
		arr[0] = i;
		for (int j = 1; j < m; j++) {
			int cost = 0;
			if (org[j - 1] != dif[i - 1]) {
				cost = 1;
			}
			int temp = arr[j];
			arr[j] = min(arr[j - 1] + 1, min(arr[j] + 1, before + cost));
			before = temp;
		}
	}
	int rst = arr[m - 1];
	delete []arr;
	return rst;
}


random_device rng;
int main() {
	InputProc input;
	input.getfile("NC_000022.11[1..50818468].fa", "Clinical  dbSNP b154 v2.BED", "ShortReads.txt");
	//이미 있는데 make호출시 shortreads.txt와 modifiedseq.txt, inputProc의 내용이 변경됨
	input.makeRandomReads(500, 80, rng);


	//1-1 첫번째과정
	//BWT알고리즘 활용
	chrono::system_clock::time_point bwt_start = chrono::system_clock::now();
	BWT bwt;
	bwt.makeBWT(input.ref);
	bwt.Restore(input.ShortReads, input.ref, input.snipPos);
	chrono::system_clock::time_point bwt_end = chrono::system_clock::now();

	
	//1-2
	//Boyer-Moore Algorithm 활용
	chrono::system_clock::time_point boyer_start = chrono::system_clock::now();
	BoyerMoore bm;
	bm.Restore(input.ShortReads, input.ref, input.snipPos);
	chrono::system_clock::time_point boyer_end = chrono::system_clock::now();

	
	//2
	//euiler로 misRead를 처리하여 sequence를 복원
	chrono::system_clock::time_point boyer_start = chrono::system_clock::now();
	Euiler bwt_euiler;
	vector<string>* restored_mis;
	restored_mis = bwt_euiler.Restore(bwt.misRead, bwt.misRead[0].length()/3);
	chrono::system_clock::time_point boyer_end = chrono::system_clock::now();


	string restored;
	//3 복원한 sequence를 1단계에서 복원한 sequence와 concat시킵니다.
	string result = Concat::concat(restored, *restored_mis);
	

	//vector<string> mis = { "00100", "10100"};
	//chrono::system_clock::time_point boyer_start = chrono::system_clock::now();
	//Euiler bwt_euiler;
	//bwt_euiler.Restore(mis, 4);
	//chrono::system_clock::time_point boyer_end = chrono::system_clock::now();
	
	//성능평가
	//cout<<calcDifference("abc", "acb");
	return 0;
}