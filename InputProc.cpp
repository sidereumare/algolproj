#include "InputProc.h"

void InputProc::getfile(const string refFile, const string snipFile, const string readsFile)
{
	ifstream fin;
	string str;

	//���۷��� �Է�
	fin.open(refFile);
	getline(fin, str);
	str.reserve(60000000);
	while (fin.peek() != EOF) {
		getline(fin, str);
		ref.append(str);
	}
	fin.close();
	cout << refFile << "�ε� �Ϸ�\n";

	//snip��ġ �Է�
	fin.open(snipFile);
	snipPos.reserve(20000);
	while (fin.peek() != EOF) {
		getline(fin, str);
		str = str.substr(13, 9);
		snipPos.push_back(stoi(str) - 1);
	}
	fin.close();
	cout << snipFile << "�ε� �Ϸ�\n";


	//N���� ǥ��� �κ� ����� snip������ ���� �κп� ���߱�
	string pn;
	vector<int> snipProcessed;
	pn.reserve(60000000);
	snipProcessed.reserve(300000);
	int cnt = 0;
	int j = 0;
	for (int i = 0; i < ref.size(); i++) {
		if (ref[i] != 'N') {
			pn.push_back(ref[i]);
			if (j < snipPos.size() && snipPos[j] == i) {				
				snipProcessed.push_back(i - cnt);
				j++;
				while (snipPos[j] == snipPos[j + 1])j++;
			}
		}
		else {
			cnt++;
		}
	}
	ref = pn;
	snipPos = snipProcessed;
	cout << "N���� �Ϸ�\n";


	//reads���� �ε� �Ϸ�
	fin.open(readsFile);
	//���� ���� ��
	if (!fin.is_open()) {
		return;
	}
	ShortReads.reserve(100000000);
	while (fin.peek() != EOF) {
		getline(fin, str);
		ShortReads.push_back(str);
	}
	fin.close();
	cout << readsFile << "�ε� �Ϸ�\n";

	fin.open("modifiedSeq.txt");
	//���� ���� ��
	if (!fin.is_open()) {
		return;
	}
	fin >> modifiedSeq;
	fin.close();
}

//�׽�Ʈ �������� ������ ���� ����
//n:���� ����, k:���� ����
void InputProc::makeRandomReads(int n, int k, random_device& rng)
{
	ifstream fin;
	string str;

	uniform_int_distribution<int> rngm(0, 1);
	string modify = ref;
	//�Ϲ����� ���� �߰�
	for (auto& i : snipPos) {
		if (rngm(rng) == 1) {
			//reference dna�� ���̸� ���������
			//A�� T�� ���� �ٲٰ�, C�� G�� ���� �ٲߴϴ�.
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

	modifiedSeq = modify;
	ofstream fout("modifiedSeq.txt");
	fout << modify;
	fout.close();


	ShortReads.clear();
	ShortReads.reserve(100000000);

	uniform_int_distribution<int> rngi(0, modify.length() - k);
	fout.open("ShortRead.txt");
	set<int> st;
	//������ ��ġ���� k ������ short read n������
	for (int i = 0; i < n; i++) {
		//�̹� ������ ��ġ�� �� �������� �ʵ��� set�� ���� �߰� �Ұ����Ҷ�����
		//insert�ݺ�
		pair<set<int>::iterator, bool> chk;
		do {
			chk = st.insert(rngi(rng));
		} while (!chk.second);

		string s = "";
		s = modify.substr(*chk.first, k);
		
		fout << s + '\n';
		ShortReads.push_back(s);
	}
	fout.close();
}

