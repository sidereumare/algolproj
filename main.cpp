#include <iostream>
#include "InputProc.h"
#include "BWT.h"
#include "BoyerMoore.h"
#include "Euiler.h"
using namespace std;

int main() {
	InputProc input;

	input.getfile("ref.txt", "readsfile.txt");

	//1-1 첫번째과정
	//BWT알고리즘 활용
	BWT bwt;
	bwt.makeBWT(input.ref);
	bwt.restore(input.ShortReads, input.ref, input.snipPos);

	//1-2
	//Boyer-Moore Algorithm 활용
	BoyerMoore bm;
	bm.restore(input.ShortReads, input.ref, input.snipPos);

	//2
	//euiler를 이용하여 misRead처리
	Euiler bwt_euiler;
	bwt_euiler.restore(bwt.misRead);



	//성능평가

	return 0;
}