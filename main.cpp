#include <iostream>
#include "InputProc.h"
#include "BWT.h"
#include "BoyerMoore.h"
#include "Euiler.h"
using namespace std;

random_device rng;
int main() {
	InputProc input;
	input.getfile("NC_000022.11[1..50818468].fa", "Clinical  dbSNP b154 v2.BED", "ShortReads.txt");
	//�̹� �ִµ� makeȣ��� shortreads.txt�� modifiedseq.txt, inputProc�� ������ �����
	input.makeRandomReads(500, 80, rng);

	//1-1 ù��°����
	//BWT�˰��� Ȱ��
	BWT bwt;
	bwt.makeBWT(input.ref);
	bwt.Restore(input.ShortReads, input.ref, input.snipPos);

	//1-2
	//Boyer-Moore Algorithm Ȱ��
	BoyerMoore bm;
	bm.Restore(input.ShortReads, input.ref, input.snipPos);

	//2
	//euiler�� �̿��Ͽ� misReadó��
	Euiler bwt_euiler;
	bwt_euiler.Restore(bwt.misRead);



	//������

	return 0;
}