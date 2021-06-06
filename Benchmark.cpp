#include "Benchmark.h"

void Benchmark::RestoreBrute(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos) {
	/* ��ġ��ũ �˰��� - �⺻���� Brute Force Alogrithm */

	//������ ���� 
	int k = ShortLeads[0].size();

	//ShortRead�� ����
	int n = ShortLeads.size();

	//reference �� ������
	int m = ref.size();

	//������ dna�� �ϴ� 'N'���� �ʱ�ȭ
	restore = "";
	restore.resize(m, 'N'); // 

	//����� mismatch �ִ� ����
	int miss_upper = 3;

	set<int> alreadyfound; // Ž���� ��ġ�ΰ�..?


	//mismatch �߻��� misRead�� ���� 
	string misRead(ref.length(), 'N');


	for (int i = 0; i < n; i++) {
		//100�� ���� üũ..?
		/*if (i % 1000 == 0) {
			cout << i << "�� read �Ϸ�\n";
		}*/

		for (int j = 0; j < m - k + 1; j++) {
			//mismatchüũ
			int mis = 0;
			bool chk = true;
			for (int l = 0; l < k; l++) { // ������ ���� ���� ���� ��
				if (ref[j + l] != ShortLeads[i][l]) { // reference�� ������ġ j�� l�� ���� �Ͱ�, shortLeads
					mis++; // �ٸ��� mis ++
					misRead.push_back(ShortLeads[i][l]);
				}
				if (mis > miss_upper) { // �ش� �ݺ������� mis�� ������ ��뼱�� ���� ���
					chk = false;
					break;
				}
			}

			//mis<miss_upper�� ��
			//restore �迭 ������Ʈ
			if (chk && alreadyfound.insert(j).second) {
				for (int l = 0; l < k; l++) {
					restore[j + l] = ShortLeads[i][l];
				}
			}
		}
	}
}

void Benchmark::RestoreKMP(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos) {
	/* ��ġ��ũ �˰��� - �⺻���� KMP Alogrithm */

	//������ ���� 
	int k = ShortLeads[0].size();

	//ShortRead�� ����
	int n = ShortLeads.size();

	//reference �� ������
	int m = ref.size();

	//������ dna�� �ϴ� 'N'���� �ʱ�ȭ
	restore = "";
	restore.resize(m, 'N'); // 

	//����� mismatch �ִ� ����
	int miss_upper = 3;

	set<int> alreadyfound; // Ž���� ��ġ�ΰ�?

	//�ƹ��͵� ã������ ������ dna
	string make(ref.length(), 'N'); // �̰� �ؾ��ϳ�..

	//mismatch �߻��� misRead�� ���� 
	string misRead(ref.length(), 'N');

	//sp���̺� 
	vector<int>* sp;


	//�� shortread �� ���徿 ������ �ݺ�
	for (int t = 0; t < n; t++) {

		//int j = 0; // ���� shortLeads�� �ε��� , �� ����
		//int l = 0; // reference�� �ε���
		//cout << ShortLeads[i];
		/* mis match üũ*/
		int mis = 0;
		bool chk = true;
		/*
		 �ǵ� : �� shortRead�� sp���̺��� ����Ϸ���..
		*/
		chrono::system_clock::time_point start = chrono::system_clock::now();
		sp = computeSP(ShortLeads[t]); //
		/*for (auto h = sp->begin(); h != sp->end(); h++)
			cout << *h << " ";*/

			//cout << ShortLeads[i]<<endl;
		int j = 0; // ���� ShortLeads���ε��� 
		for (int i = 0; i < m; i++) {
			while (j > 0 && ShortLeads[t].at(j) != ref.at(i))
				j = sp->at(j - 1); // 0���� �����ؼ� j-1
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
				cout << mis << "�ȸ¾�" << endl;
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
		cout << "��Ʈ����� ref �� \n";
		cout << chrono::duration<double>(end - start).count() << '\n';
		cout << "�������Գ� t" << t << endl;

	}
}

vector<int>* Benchmark::computeSP(const string ShortLeads) { //�� shortRead�� �� ���徿..?

	int k = ShortLeads.size();  //������ ���� 

		//cout << k <<"short read ����"<< endl;
	vector<int>* sp = new vector<int>(k, 0); // vector �����̳� ũ��, �� ���ҿ� �Ҵ��� ��
	//prefix�� suffix ���̺� �����

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
//	/* ��ġ��ũ �˰��� - �⺻���� KMP Alogrithm */
//
//	//������ ���� 
//	int k = ShortLeads[0].size();
//
//	//ShortRead�� ����
//	int n = ShortLeads.size();
//
//	//reference �� ������
//	int m = ref.size();
//
//	//������ dna�� �ϴ� 'N'���� �ʱ�ȭ
//	restore = "";
//	restore.resize(m, 'N'); // 
//
//	//����� mismatch �ִ� ����
//	int miss_upper = 3;
//
//	set<int> alreadyfound; // Ž���� ��ġ�ΰ�?
//
//	//�ƹ��͵� ã������ ������ dna
//	string make(ref.length(), 'N'); // �̰� �ؾ��ϳ�..
//
//	//mismatch �߻��� misRead�� ���� 
//	string misRead(ref.length(), 'N');
//
//	//sp���̺� 
//	int* sp = new int[k];
//
//
//
//	//�� shortread �� ���徿 ������ �ݺ�
//	for (int i = 0; i < n; i++) {
//
//		int j = 0; // ���� shortLeads�� �ε��� , �� ����
//		int l = 0; // reference�� �ε���
//
//		/* mis match üũ*/
//		int mis = 0;
//		bool chk = true;
//		/*
//		 �ǵ� : �� shortRead�� sp���̺��� ����Ϸ���..
//		*/
//		sp = computeSP(ShortLeads[i]); //
//		while (l < m) { // l<ref�� ���̺��� ���� �� 
//
//			if (ShortLeads[i][j] == ref[l]) {
//				j++;
//				l++;
//			}
//			if (j == k) { // ���� ���̿� ���ٸ�
//				//cout << "Found ShortLeads[i][j] pattern here %d \n"<< i-j; //�̰Ŵ���..
//				j = sp[j - 1];
//			}
//			/* ���⼭ ���� �߰� ��� �ʿ���..*/
//			else if (l < m && ShortLeads[i][j] != ref[l]) { //
//				//sp[0..sp[j-1]]�� �ȸ��� ��,  
//				mis++;
//				misRead.push_back(ShortLeads[i][l]);
//				if (mis > miss_upper) { // �ش� �ݺ������� mis�� ������ ��뼱�� ���� ���
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
//		//mis<miss_upper�� ��
//		//restore �迭 ������Ʈ
//		if (chk && alreadyfound.insert(j).second) {
//			for (int l = 0; l < k; l++) {
//				restore[j + l] = ShortLeads[i][l];
//			}
//		}
//
//	}
//}
