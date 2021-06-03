#include <iostream>
#include <chrono>
#include "InputProc.h"
#include "BWT.h"
#include "BoyerMoore.h"
#include "Euiler.h"
#include "Concat.h"
using namespace std;

//�ּ� �����Ÿ��� �̿��Ͽ� ���� ��
//�ð����⵵ O(mn), �������⵵ O(m)
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
	//�̹� �ִµ� makeȣ��� shortreads.txt�� modifiedseq.txt, inputProc�� ������ �����
	input.makeRandomReads(500, 80, rng);


	//1-1 ù��°����
	//BWT�˰��� Ȱ��
	chrono::system_clock::time_point bwt_start = chrono::system_clock::now();
	BWT bwt;
	bwt.makeBWT(input.ref);
	bwt.Restore(input.ShortReads, input.ref, input.snipPos);
	chrono::system_clock::time_point bwt_end = chrono::system_clock::now();

	
	//1-2
	//Boyer-Moore Algorithm Ȱ��
	chrono::system_clock::time_point boyer_start = chrono::system_clock::now();
	BoyerMoore bm;
	bm.Restore(input.ShortReads, input.ref, input.snipPos);
	chrono::system_clock::time_point boyer_end = chrono::system_clock::now();

	
	//2
	//euiler�� misRead�� ó���Ͽ� sequence�� ����
	chrono::system_clock::time_point boyer_start = chrono::system_clock::now();
	Euiler bwt_euiler;
	vector<string>* restored_mis;
	restored_mis = bwt_euiler.Restore(bwt.misRead, bwt.misRead[0].length()/3);
	chrono::system_clock::time_point boyer_end = chrono::system_clock::now();


	string restored;
	//3 ������ sequence�� 1�ܰ迡�� ������ sequence�� concat��ŵ�ϴ�.
	string result = Concat::concat(restored, *restored_mis);
	

	//vector<string> mis = { "00100", "10100"};
	//chrono::system_clock::time_point boyer_start = chrono::system_clock::now();
	//Euiler bwt_euiler;
	//bwt_euiler.Restore(mis, 4);
	//chrono::system_clock::time_point boyer_end = chrono::system_clock::now();
	
	//������
	//cout<<calcDifference("abc", "acb");
	return 0;
}