#include "BoyerMoore.h"

void BoyerMoore::Restore(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos)
{
    // 패턴의 길이 k
    int k = ShortLeads[0].size();

    // shortread 개수 N
    int n = ShortLeads.size();

    // ref의 size
    int m = ref.size();

    // 복원할 dna를 일단 'N'으로 초기화
    restore = "";
    restore.resize(m, 'N');

    int miss = 3;

    auto func = [this, &ShortLeads, &snipPos, &ref, &n, &m, &k, &miss](int s) {

        for (int i = 0; i < n; i++) {
            int missNum = 0;
            int badchar[256]; // 256은 문자의 개수
            // bad char 배열을 현재 short_read에 맞게 채운다.
            badCharHeuristic(ShortLeads[i], k, badchar);

            int* bpos = new int[k + 1];
            int* shift = new int[k + 1];
            for (int l = 0; l < k + 1; l++)shift[l] = 0;
            good_suffix_Heuristic(shift, bpos, ShortLeads[i], k);
            preprocess_case2(shift, bpos, ShortLeads[i], k);

            char firstCh = ShortLeads[i][0];   // 패턴의 첫 문자
            char middleCh = ShortLeads[i][k / 2]; // 패턴의 중간 문자
            char lastCh = ShortLeads[i][k - 1];   // 패턴의 끝 문자
            char c;   // 현재 문자 임시 저장 용도

            int s = 0; // s는 현재 shortread가 가리키는 ref에서의 위치
            while (s <= (m - k)) {
                int j = k - 1;
                int missNum = 0; // 대입 비교하며 찾은 missmatch 개수

                c = ref[s + k - 1];
                if (lastCh != c)missNum++;
                if (middleCh != ref[s + k / 2])missNum++;
                if (firstCh != ref[s])missNum++;
                if (missNum > miss) {
                    s += max(1, shift[j]);

                }

                // 패턴에서 현재 가리키는 문자와 레퍼런스에서 현재 가리키는 문자가 같다면 계속 j를 shortread의 마지막에서부터 줄여간다.
                // 오->왼 순으로 비교해 나간다.
                while (j >= 0) {
                    if (j == s + k - 1 || j == s + k / 2 || j == s) { // 첫번째 글자, 중간 글자, 마지막 글자는 이미 확인 했으니 패스
                        j--;
                        continue;
                    }
                    if (ShortLeads[i][j] == ref[s + j]) { // shortread와 ref가 가리키는 문자가 같을 경우
                        j--;
                    }
                    else { // missMatch가 생기면 그만두기
                        if (missNum <= miss) {
                            missNum++;
                        }
                        else {
                            break;
                        }
                    }
                }
                // 패턴이 현재 위치에 존재하는 것이 확인되었다면, j는 -1일 것이다.
                if (j < 0 && missNum <= miss) {
                    // 그러면 복원을 진행한다.
                    for (int z = 0; z < k; z++) {
                        restore[s + z] = ShortLeads[i][z];
                    }
                    break; // 다음 short_read로 넘어간다.
                }
                else {
                    // 패턴이 현재 위치에 있지 않다면 다른 위치에서 패턴을 찾아야 한다.
                    // 옆으로 얼마나 옮길지는 badchar에 저장된 값을 기준으로 설정한다.
                    int plus = max(1, j - badchar[ref[s + j]]);
                    s += max(plus, shift[j + 1]);
                    //s += plus;
                }
            }
            if (s >= m - k) {
                _mutex.lock();
                misRead.push_back(ShortLeads[i]);
                _mutex.unlock();
            }
            delete[] shift;
            delete[] bpos;
        }
    };

    vector<thread> t;
    for (int i = 0; i < 10; i++) {
        t.push_back(thread(func, i));
    }
    for (auto& e : t) {
        e.join();
    }


}



void BoyerMoore::badCharHeuristic(const string pattern, const int size, int* badchar) {
    int i;

    // 모든 출현 위치를 -1로 초기화한다.
    for (i = 0; i < 256; i++)
        badchar[i] = -1;

    // 그리고 실제 값을 제일 마지막 출현 위치로 바꾼다.
    for (i = 0; i < size; i++)
        badchar[(int)pattern[i]] = i;
}

void BoyerMoore::good_suffix_Heuristic(int* shift, int* bpos, string pattern, int m) {
    int i = m, j = m + 1;
    bpos[i] = j;

    while (i > 0)
    {
        while (j <= m && pattern[i - 1] != pattern[j - 1])
        {
            if (shift[j] == 0)
                shift[j] = j - i;

            j = bpos[j];
        }

        i--; j--;
        bpos[i] = j;
    }
}

void BoyerMoore::preprocess_case2(int* shift, int* bpos, string pattern, int m) {
    int i, j;
    j = bpos[0];
    for (i = 0; i <= m; i++)
    {

        if (shift[i] == 0)
            shift[i] = j;

        if (i == j)
            j = bpos[j];
    }
}
