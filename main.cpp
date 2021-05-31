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
	//이미 있는데 make호출시 shortreads.txt와 modifiedseq.txt, inputProc의 내용이 변경됨
	input.makeRandomReads(500, 80, rng);

	//1-1 첫번째과정
	//BWT알고리즘 활용
	BWT bwt;
	bwt.makeBWT(input.ref);
	bwt.Restore(input.ShortReads, input.ref, input.snipPos);

	//1-2
	//Boyer-Moore Algorithm 활용
	BoyerMoore bm;
	bm.Restore(input.ShortReads, input.ref, input.snipPos);

	//2
	//euiler를 이용하여 misRead처리
	Euiler bwt_euiler;
	bwt_euiler.Restore(bwt.misRead);



	//성능평가

	return 0;
}