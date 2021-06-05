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


    // 1. Boyer Moore 기본 알고리즘
/*
     for(int i=0; i<n; i++){
        int badchar[256]; // 256은 문자의 개수
        int skip_tb[m+1]; // 몇개 건너 뛸 수 있는지 알려주는 테이블

        // bad char 배열을 현재 short_read에 맞게 채운다.
        badCharHeuristic(ShortLeads[i], k, badchar);

        // good_suffix에 대한 테이블 만들기 (생략할 문자 개수에 대한 테이블)
        make_gs_table(ShortLeads[i], skip_tb);

        int s = 0; // s는 현재 shortread가 가리키는 ref에서의 위치
        while(s<=(m-k)){
            int j = k-1;
            int missNum = 0; // 대입 비교하며 찾은 missmatch 개수

            // 패턴에서 현재 가리키는 문자와 레퍼런스에서 현재 가리키는 문자가 같다면 계속 j를 shortread의 마지막에서부터 줄여간다.
            // 오->왼 순으로 비교해 나간다.
            while(j>=0){
                if(ShortLeads[i][j] == ref[s+j]){ // shortread와 ref가 가리키는 문자가 같을 경우
                    j--;
                }
                else{ // missMatch 발생시 그만두기
                    break;
                }
            }

            // 패턴이 현재 위치에 존재하는 것이 확인되었다면, j는 -1일 것이다.
            if(j<0){
                // 그러면 복원을 진행한다.
                for(int z=0; z<m; z++){
                    restore[s+z] = ShortLeads[i][z];
                }
                break; // 다음 short_read로 넘어간다.
            }else{
                // 패턴이 현재 위치에 있지 않다면 다른 위치에서 패턴을 찾아야 한다.
                // 옆으로 얼마나 옮길지는 badchar에 저장된 값을 기준으로 설정한다.
                int plus = max(1,j-badchar[ref[s+j]]);
                s += max(plus, skip_tb[j]);
            }

        }
        if(s >= m-k){
            misRead.push_back(ShortLeads[i]);
        }
    }

*/


// 2. Boyer moore Horspool  알고리즘 이용하기
// 기본 알고리즘에서 suffix가 같은 부분을 이용해 생략할 문자의 개수 찾는 부분을 없앰
// short_read를 처음부터 끝까지 돌며 위치 찾아내기
    /*
    for(int i=0; i<n; i++){
        int badchar[256]; // 256은 문자의 개수

        // bad char 배열을 현재 short_read에 맞게 채운다.
        badCharHeuristic(ShortLeads[i], k, badchar);

        int s = 0; // s는 현재 shortread가 가리키는 ref에서의 위치
        while(s<=(m-k)){
            int j = k-1;
            int missNum = 0; // 대입 비교하며 찾은 missmatch 개수

            // 패턴에서 현재 가리키는 문자와 레퍼런스에서 현재 가리키는 문자가 같다면 계속 j를 shortread의 마지막에서부터 줄여간다.
            // 오->왼 순으로 비교해 나간다.
            while(j>=0){
                if(ShortLeads[i][j] == ref[s+j] || binary_search(snipPos.begin(), snipPos.end(), s+j)){ // shortread와 ref가 가리키는 문자가 같을 경우
                    j--;
                }else{ // missMatch가 생기면 그만두기
                    break;
                }
            }

            // 패턴이 현재 위치에 존재하는 것이 확인되었다면, j는 -1일 것이다.
            if(j<0){
                // 그러면 복원을 진행한다.
                for(int z=0; z<k; z++){
                    restore[s+z] = ShortLeads[i][z];
                }
                break; // 다음 short_read로 넘어간다.
            }else{
                // 패턴이 현재 위치에 있지 않다면 다른 위치에서 패턴을 찾아야 한다.
                // 옆으로 얼마나 옮길지는 badchar에 저장된 값을 기준으로 설정한다.
                s += max(1, j-badchar[ref[s+j]]);
            }

        }
        if(s >= m-k){
            misRead.push_back(ShortLeads[i]);
        }
    }
    */



/*  3. Boyer moore horspool 에서 조금 기능 추가한 Raita 알고리즘
 * boyer moore에서는 모든 shortread를 일일이 비교해 보았다면
 * Raita에서는 각 shortread가 새로운 위치에 놓이면 패턴의 첫글자, 중간글자, 마지막 글자 비교를 진행한다.
 * 그리고 하나라도 missmatch되면 패스 하는 방식으로 시간을 줄인다.
 */
 /*
for(int i=0; i<n; i++){
    int badchar[256]; // 256은 문자의 개수

    // bad char 배열을 현재 short_read에 맞게 채운다.
    badCharHeuristic(ShortLeads[i], k, badchar);

    int s = 0; // s는 현재 shortread가 가리키는 ref에서의 위치

    char firstCh = ShortLeads[i][0];   // 패턴의 첫 문자
    char middleCh = ShortLeads[i][k/2]; // 패턴의 중간 문자
    char lastCh = ShortLeads[i][k-1];   // 패턴의 끝 문자
    char c;   // 현재 문자 임시 저장 용도

    while(s<=(m-k)){
        int j = k-1;

        c = ref[s+m-1];

        // Raita에서는 처음문자 중간문자 끝 문자가 같은지 먼저 비교한다.
        if(lastCh == c) {
            if (middleCh == ref[s + m / 2]) {
                if (firstCh == ref[s]) {
                    // 패턴에서 현재 가리키는 문자와 레퍼런스에서 현재 가리키는 문자가 같다면 계속 j를 shortread의 마지막에서부터 줄여간다.
                    // 오->왼 순으로 비교해 나간다.
                    while (j >= 0) {
                        if (j == s + k - 1 || j == s + k / 2 || j == s) { // 첫번째 글자, 중간 글자, 마지막 글자는 이미 확인 했으니 패스
                            j--;
                            continue;
                        }
                        if (ShortLeads[i][j] == ref[s + j]) { // shortread와 ref가 가리키는 문자가 같을 경우
                            j--;
                        }else { // missMatch가 발생하면 그만두기
                            break;
                        }
                    }

                    // 패턴이 현재 위치에 존재하는 것이 확인되었다면, j는 -1일 것이다.
                    if (j < 0) {
                        // 그러면 복원을 진행한다.
                        for (int z = 0; z < m; z++) {
                            restore[s + z] = ShortLeads[i][z];
                        }
                        break; // 다음 short_read로 넘어간다.
                    } else {
                        // 패턴이 현재 위치에 있지 않다면 다른 위치에서 패턴을 찾아야 한다.
                        // 옆으로 얼마나 옮길지는 badchar에 저장된 값을 기준으로 설정한다.
                        s += max(1, j - badchar[ref[s + j]]);
                    }
                }
            }
        }
        s += max(1,badchar[c]);

    }
    if(s >= m-k){
        misRead.push_back(ShortLeads[i]);
    }
}
 */




 // 4. 기본 boyer moore알고리즘에 Raita 알고리즘 적용하기

    for (int i = 0; i < n; i++) {
        int badchar[256]; // 256은 문자의 개수
        int *skip_tb = new int[m + 1]; // 몇개 건너 뛸 수 있는지 알려주는 테이블

        // bad char 배열을 현재 short_read에 맞게 채운다.
        badCharHeuristic(ShortLeads[i], k, badchar);
        // good_suffix에 대한 테이블 만들기 (생략할 문자 개수에 대한 테이블)
        make_gs_table(ShortLeads[i], skip_tb);

        int s = 0; // s는 현재 shortread가 가리키는 ref에서의 위치

        char firstCh = ShortLeads[i][0];   // 패턴의 첫 문자
        char middleCh = ShortLeads[i][k / 2]; // 패턴의 중간 문자
        char lastCh = ShortLeads[i][k - 1];   // 패턴의 끝 문자
        char c;   // 현재 문자 임시 저장 용도

        while (s <= (m - k)) {
            int j = k - 1;
            int missNum = 0; // 대입 비교하며 찾은 missmatch 개수

            c = ref[s + k - 1];

            // Raita에서는 처음문자 중간문자 끝 문자가 같은지 먼저 비교한다.
            if (lastCh == c || binary_search(snipPos.begin(), snipPos.end(), s + k -1)) {
                if (middleCh == ref[s + k / 2] || binary_search(snipPos.begin(), snipPos.end(), s + k / 2)) {
                    if (firstCh == ref[s] || binary_search(snipPos.begin(), snipPos.end(), s)) {

                        // 패턴에서 현재 가리키는 문자와 레퍼런스에서 현재 가리키는 문자가 같다면 계속 j를 shortread의 마지막에서부터 줄여간다.
                        // 오->왼 순으로 비교해 나간다.
                        while (j >= 0) {
                            if (j == s + k - 1 || j == s + k / 2 || j == s) { // 첫번째 글자, 중간 글자, 마지막 글자는 이미 확인 했으니 패스
                                j--;
                                continue;
                            }
                            if (ShortLeads[i][j] == ref[s + j] || binary_search(snipPos.begin(), snipPos.end(), s + j)) { // shortread와 ref가 가리키는 문자가 같을 경우, snip인 경우
                                j--;
                            }
                            else { // missMatch 가 발생하면 그만두기
                                break;
                            }
                        }

                        // 패턴이 현재 위치에 존재하는 것이 확인되었다면, j는 -1일 것이다.
                        if (j < 0) {
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
                            s += max(plus, skip_tb[j]);
                        }
                    }
                }
            }
            s += max(1, badchar[c]);
        }
        if (s >= m - k) {
            misRead.push_back(ShortLeads[i]);
        }
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


void BoyerMoore::make_gs_table(const string pattern, int* skip_tb) {
    const int p_size = pattern.size();

    int pattern_point = p_size;
    int suffix_point = pattern_point + 1;

    // 접미사와 동일한 문자열 체크하는 테이블
    int *suf_tb = new int[p_size + 1];
    suf_tb[pattern_point] = suffix_point;

    while (pattern_point > 0) {
        //cout<<'h'<<endl;
        // 접미사가 일치하는 순간 몇개가 일치하는지 카운팅한다.
        while (suffix_point <= p_size && pattern[pattern_point - 1] != pattern[suffix_point - 1]) {
            if (skip_tb[suffix_point] == 0)
                skip_tb[suffix_point] = suffix_point - pattern_point;
            suffix_point = suf_tb[suffix_point];
        }

        // 접미사와 동일한 단어가 접미사 인덱스를 가리키도록 설정
        suf_tb[--pattern_point] = --suffix_point;
    }

    suffix_point = suf_tb[0];
    while (pattern_point < p_size) {
        if (skip_tb[pattern_point] == 0)
            skip_tb[pattern_point] = suffix_point;
        if (pattern_point++ == suffix_point)
            suffix_point = suf_tb[suffix_point];
    }

}