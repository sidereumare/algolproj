#include <iostream>
#include <chrono>
#include "InputProc.h"
#include "BWT.h"
#include "BoyerMoore.h"
#include "Euiler.h"
#include "Concat.h"
#include "Benchmark.h"

using namespace std;

//�ּ� �����Ÿ��� �̿��Ͽ� ���� ��
//�ð����⵵ O(mn), �������⵵ O(m)
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


random_device rng;
int main() {
	
	//30000000
	InputProc input;
	input.getfile("NC_000022.11[1..50818468].fa", "Clinical  dbSNP b154 v2.BED", "ShortRead.txt");
	//cout << input.ref.size();
	//return 0;
	//�̹� �ִµ� makeȣ��� shortreads.txt�� modifiedseq.txt, inputProc�� ������ �����
	cout << "����� ���۷����� ���̸� �Է��� �ּ���\n";
	int ref_len;
	cin >> ref_len;
	input.ref = input.ref.substr(0, ref_len);
	input.makeRandomReads(ref_len/2, 100, rng);
	cout << "������ �����Ϸ�" << '\n';

	//1-1 ù��°����
	//BWT�˰��� Ȱ��
	chrono::system_clock::time_point bwt_start = chrono::system_clock::now();
	BWT bwt;
	bwt.makeBWT(input.ref);
	bwt.Restore(input.ShortReads, input.ref, input.snipPos);
	chrono::system_clock::time_point bwt_end = chrono::system_clock::now();
	cout << "BWT�Ϸ�\n";
	cout << chrono::duration<double>(bwt_end - bwt_start).count() << '\n';

	//2-1
	//euiler�� BWT�� ������� misRead�� ó���Ͽ� sequence�� ����
	chrono::system_clock::time_point euiler_start = chrono::system_clock::now();
	Euiler bwt_euiler;
	vector<string>* restored_mis;
	restored_mis = bwt_euiler.Restore(bwt.misRead, 61);
	chrono::system_clock::time_point euiler_end = chrono::system_clock::now();
	cout << "euiler�Ϸ�\n";
	cout << chrono::duration<double>(euiler_end - euiler_start).count() << '\n';

	//3-1 ������ sequence�� 1-2�ܰ迡�� ������ sequence�� concat��ŵ�ϴ�.
	chrono::system_clock::time_point concat_start = chrono::system_clock::now();
	Concat con;
	string result = con.concat(bwt.restore, *restored_mis);
	chrono::system_clock::time_point concat_end = chrono::system_clock::now();
	cout << "Construct�Ϸ�\n";
	cout << chrono::duration<double>(concat_end - concat_start).count() << '\n';
	
	
	ofstream fout("1-1reconstructed.txt");
	fout << result;
	fout.close();
	//int rst = calcDifference(input.modifiedSeq, result);
	//cout << rst << '\n';

	


	////1-2
	//Boyer-Moore Algorithm Ȱ��
	chrono::system_clock::time_point boyer_start = chrono::system_clock::now();
	BoyerMoore bm;
	bm.Restore(input.ShortReads, input.ref, input.snipPos);
	chrono::system_clock::time_point boyer_end = chrono::system_clock::now();
	cout << "Boyer-Moore�Ϸ�\n";
	cout << chrono::duration<double>(boyer_end - boyer_start).count() << '\n';

	//2-2
	//euiler�� Boyer-Moore �� ������� misRead�� ó���Ͽ� sequence�� ����
	chrono::system_clock::time_point euiler_start1 = chrono::system_clock::now();
	Euiler bm_euiler;
	vector<string>* restored_mis1;
	restored_mis1 = bm_euiler.Restore(bm.misRead, 71);
	chrono::system_clock::time_point euiler_end1 = chrono::system_clock::now();
	cout << "Euiler�Ϸ�\n";
	cout << chrono::duration<double>(euiler_end1 - euiler_start1).count() << '\n';

	//3-2 ������ sequence�� 1-2�ܰ迡�� ������ sequence�� concat��ŵ�ϴ�.
	chrono::system_clock::time_point concat_start1 = chrono::system_clock::now();
	Concat con1;
	string result1 = con1.concat(bm.restore, *restored_mis1);
	chrono::system_clock::time_point concat_end1 = chrono::system_clock::now();
	cout << "Construct�Ϸ�\n";
	cout << chrono::duration<double>(concat_end1 - concat_start1).count() << '\n';

	fout.open("1-2reconstructed.txt");
	fout << result1;
	fout.close();

	//int rst = calcDifference(input.modifiedSeq, result1);
	//cout << rst << '\n';

	
	//���� ��ġ��ũ��	
	Benchmark bench;
	//��ġ��ũ ����
	chrono::system_clock::time_point bench_start = chrono::system_clock::now();
	bench.RestoreKMP(input.ShortReads, input.ref, input.snipPos);
	chrono::system_clock::time_point bench_end = chrono::system_clock::now();
	cout << "bench����\n";
	cout << chrono::duration<double>(bench_end - bench_start).count() << '\n';
	fout.open("benchmarkreconstructed.txt");
	fout << result1;
	fout.close();


	Benchmark bench1;
	cout << "benchmark ����\n";
	chrono::system_clock::time_point bench_start1 = chrono::system_clock::now();
	bench1.RestoreBrute(input.ShortReads, input.ref, input.snipPos);
	chrono::system_clock::time_point bench_end1 = chrono::system_clock::now();
	cout << "Construct�Ϸ�\n";
	cout << chrono::duration<double>(bench_end1 - bench_start1).count() << '\n';
	ofstream fout("benchmarkreconstructed.txt");
	fout << bench1.restore;
	fout.close();








	//vector<string> mis = { "00100", "10100"};
	//chrono::system_clock::time_point boyer_start = chrono::system_clock::now();
	//Euiler bwt_euiler;
	//bwt_euiler.Restore(mis, 4);
	//chrono::system_clock::time_point boyer_end = chrono::system_clock::now();

	//������
	//cout<<calcDifference("abc", "acb");
	

	//�׽�Ʈ
	//BWT bw;
	//string ref = "ACAACG";
	//vector<int> snippos = { 0 };
	//vector<string> r = {"TCA","CAA","AAC","ACG"};
	//bw.Restore(r, ref, snippos);
	//cout<<Concat::concat("abcdNNadcNNe", { "cdfad", "adce" });
	return 0;
}