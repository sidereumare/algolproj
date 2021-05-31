#include <iostream>
#include "InputProc.h"
#include "BWT.h"
#include "BoyerMoore.h"
#include "Euiler.h"
using namespace std;

int main() {
	InputProc input;

	input.getfile("ref.txt", "readsfile.txt");

	//1-1 ù��°����
	//BWT�˰��� Ȱ��
	BWT bwt;
	bwt.makeBWT(input.ref);
	bwt.restore(input.ShortReads, input.ref, input.snipPos);

	//1-2
	//Boyer-Moore Algorithm Ȱ��
	BoyerMoore bm;
	bm.restore(input.ShortReads, input.ref, input.snipPos);

	//2
	//euiler�� �̿��Ͽ� misReadó��
	Euiler bwt_euiler;
	bwt_euiler.restore(bwt.misRead);



	//������

	return 0;
}