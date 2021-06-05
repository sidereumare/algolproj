#include "BoyerMoore.h"

void BoyerMoore::Restore(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos)
{


    // ������ ���� k
    int k = ShortLeads[0].size();

    // shortread ���� N
    int n = ShortLeads.size();

    // ref�� size
    int m = ref.size();

    // ������ dna�� �ϴ� 'N'���� �ʱ�ȭ
    restore = "";
    restore.resize(m, 'N');


    // 1. Boyer Moore �⺻ �˰���
/*
     for(int i=0; i<n; i++){
        int badchar[256]; // 256�� ������ ����
        int skip_tb[m+1]; // � �ǳ� �� �� �ִ��� �˷��ִ� ���̺�

        // bad char �迭�� ���� short_read�� �°� ä���.
        badCharHeuristic(ShortLeads[i], k, badchar);

        // good_suffix�� ���� ���̺� ����� (������ ���� ������ ���� ���̺�)
        make_gs_table(ShortLeads[i], skip_tb);

        int s = 0; // s�� ���� shortread�� ����Ű�� ref������ ��ġ
        while(s<=(m-k)){
            int j = k-1;
            int missNum = 0; // ���� ���ϸ� ã�� missmatch ����

            // ���Ͽ��� ���� ����Ű�� ���ڿ� ���۷������� ���� ����Ű�� ���ڰ� ���ٸ� ��� j�� shortread�� �������������� �ٿ�����.
            // ��->�� ������ ���� ������.
            while(j>=0){
                if(ShortLeads[i][j] == ref[s+j]){ // shortread�� ref�� ����Ű�� ���ڰ� ���� ���
                    j--;
                }
                else{ // missMatch �߻��� �׸��α�
                    break;
                }
            }

            // ������ ���� ��ġ�� �����ϴ� ���� Ȯ�εǾ��ٸ�, j�� -1�� ���̴�.
            if(j<0){
                // �׷��� ������ �����Ѵ�.
                for(int z=0; z<m; z++){
                    restore[s+z] = ShortLeads[i][z];
                }
                break; // ���� short_read�� �Ѿ��.
            }else{
                // ������ ���� ��ġ�� ���� �ʴٸ� �ٸ� ��ġ���� ������ ã�ƾ� �Ѵ�.
                // ������ �󸶳� �ű����� badchar�� ����� ���� �������� �����Ѵ�.
                int plus = max(1,j-badchar[ref[s+j]]);
                s += max(plus, skip_tb[j]);
            }

        }
        if(s >= m-k){
            misRead.push_back(ShortLeads[i]);
        }
    }

*/


// 2. Boyer moore Horspool  �˰��� �̿��ϱ�
// �⺻ �˰��򿡼� suffix�� ���� �κ��� �̿��� ������ ������ ���� ã�� �κ��� ����
// short_read�� ó������ ������ ���� ��ġ ã�Ƴ���
    /*
    for(int i=0; i<n; i++){
        int badchar[256]; // 256�� ������ ����

        // bad char �迭�� ���� short_read�� �°� ä���.
        badCharHeuristic(ShortLeads[i], k, badchar);

        int s = 0; // s�� ���� shortread�� ����Ű�� ref������ ��ġ
        while(s<=(m-k)){
            int j = k-1;
            int missNum = 0; // ���� ���ϸ� ã�� missmatch ����

            // ���Ͽ��� ���� ����Ű�� ���ڿ� ���۷������� ���� ����Ű�� ���ڰ� ���ٸ� ��� j�� shortread�� �������������� �ٿ�����.
            // ��->�� ������ ���� ������.
            while(j>=0){
                if(ShortLeads[i][j] == ref[s+j] || binary_search(snipPos.begin(), snipPos.end(), s+j)){ // shortread�� ref�� ����Ű�� ���ڰ� ���� ���
                    j--;
                }else{ // missMatch�� ����� �׸��α�
                    break;
                }
            }

            // ������ ���� ��ġ�� �����ϴ� ���� Ȯ�εǾ��ٸ�, j�� -1�� ���̴�.
            if(j<0){
                // �׷��� ������ �����Ѵ�.
                for(int z=0; z<k; z++){
                    restore[s+z] = ShortLeads[i][z];
                }
                break; // ���� short_read�� �Ѿ��.
            }else{
                // ������ ���� ��ġ�� ���� �ʴٸ� �ٸ� ��ġ���� ������ ã�ƾ� �Ѵ�.
                // ������ �󸶳� �ű����� badchar�� ����� ���� �������� �����Ѵ�.
                s += max(1, j-badchar[ref[s+j]]);
            }

        }
        if(s >= m-k){
            misRead.push_back(ShortLeads[i]);
        }
    }
    */



/*  3. Boyer moore horspool ���� ���� ��� �߰��� Raita �˰���
 * boyer moore������ ��� shortread�� ������ ���� ���Ҵٸ�
 * Raita������ �� shortread�� ���ο� ��ġ�� ���̸� ������ ù����, �߰�����, ������ ���� �񱳸� �����Ѵ�.
 * �׸��� �ϳ��� missmatch�Ǹ� �н� �ϴ� ������� �ð��� ���δ�.
 */
 /*
for(int i=0; i<n; i++){
    int badchar[256]; // 256�� ������ ����

    // bad char �迭�� ���� short_read�� �°� ä���.
    badCharHeuristic(ShortLeads[i], k, badchar);

    int s = 0; // s�� ���� shortread�� ����Ű�� ref������ ��ġ

    char firstCh = ShortLeads[i][0];   // ������ ù ����
    char middleCh = ShortLeads[i][k/2]; // ������ �߰� ����
    char lastCh = ShortLeads[i][k-1];   // ������ �� ����
    char c;   // ���� ���� �ӽ� ���� �뵵

    while(s<=(m-k)){
        int j = k-1;

        c = ref[s+m-1];

        // Raita������ ó������ �߰����� �� ���ڰ� ������ ���� ���Ѵ�.
        if(lastCh == c) {
            if (middleCh == ref[s + m / 2]) {
                if (firstCh == ref[s]) {
                    // ���Ͽ��� ���� ����Ű�� ���ڿ� ���۷������� ���� ����Ű�� ���ڰ� ���ٸ� ��� j�� shortread�� �������������� �ٿ�����.
                    // ��->�� ������ ���� ������.
                    while (j >= 0) {
                        if (j == s + k - 1 || j == s + k / 2 || j == s) { // ù��° ����, �߰� ����, ������ ���ڴ� �̹� Ȯ�� ������ �н�
                            j--;
                            continue;
                        }
                        if (ShortLeads[i][j] == ref[s + j]) { // shortread�� ref�� ����Ű�� ���ڰ� ���� ���
                            j--;
                        }else { // missMatch�� �߻��ϸ� �׸��α�
                            break;
                        }
                    }

                    // ������ ���� ��ġ�� �����ϴ� ���� Ȯ�εǾ��ٸ�, j�� -1�� ���̴�.
                    if (j < 0) {
                        // �׷��� ������ �����Ѵ�.
                        for (int z = 0; z < m; z++) {
                            restore[s + z] = ShortLeads[i][z];
                        }
                        break; // ���� short_read�� �Ѿ��.
                    } else {
                        // ������ ���� ��ġ�� ���� �ʴٸ� �ٸ� ��ġ���� ������ ã�ƾ� �Ѵ�.
                        // ������ �󸶳� �ű����� badchar�� ����� ���� �������� �����Ѵ�.
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




 // 4. �⺻ boyer moore�˰��� Raita �˰��� �����ϱ�

    for (int i = 0; i < n; i++) {
        int badchar[256]; // 256�� ������ ����
        int *skip_tb = new int[m + 1]; // � �ǳ� �� �� �ִ��� �˷��ִ� ���̺�

        // bad char �迭�� ���� short_read�� �°� ä���.
        badCharHeuristic(ShortLeads[i], k, badchar);
        // good_suffix�� ���� ���̺� ����� (������ ���� ������ ���� ���̺�)
        make_gs_table(ShortLeads[i], skip_tb);

        int s = 0; // s�� ���� shortread�� ����Ű�� ref������ ��ġ

        char firstCh = ShortLeads[i][0];   // ������ ù ����
        char middleCh = ShortLeads[i][k / 2]; // ������ �߰� ����
        char lastCh = ShortLeads[i][k - 1];   // ������ �� ����
        char c;   // ���� ���� �ӽ� ���� �뵵

        while (s <= (m - k)) {
            int j = k - 1;
            int missNum = 0; // ���� ���ϸ� ã�� missmatch ����

            c = ref[s + k - 1];

            // Raita������ ó������ �߰����� �� ���ڰ� ������ ���� ���Ѵ�.
            if (lastCh == c || binary_search(snipPos.begin(), snipPos.end(), s + k -1)) {
                if (middleCh == ref[s + k / 2] || binary_search(snipPos.begin(), snipPos.end(), s + k / 2)) {
                    if (firstCh == ref[s] || binary_search(snipPos.begin(), snipPos.end(), s)) {

                        // ���Ͽ��� ���� ����Ű�� ���ڿ� ���۷������� ���� ����Ű�� ���ڰ� ���ٸ� ��� j�� shortread�� �������������� �ٿ�����.
                        // ��->�� ������ ���� ������.
                        while (j >= 0) {
                            if (j == s + k - 1 || j == s + k / 2 || j == s) { // ù��° ����, �߰� ����, ������ ���ڴ� �̹� Ȯ�� ������ �н�
                                j--;
                                continue;
                            }
                            if (ShortLeads[i][j] == ref[s + j] || binary_search(snipPos.begin(), snipPos.end(), s + j)) { // shortread�� ref�� ����Ű�� ���ڰ� ���� ���, snip�� ���
                                j--;
                            }
                            else { // missMatch �� �߻��ϸ� �׸��α�
                                break;
                            }
                        }

                        // ������ ���� ��ġ�� �����ϴ� ���� Ȯ�εǾ��ٸ�, j�� -1�� ���̴�.
                        if (j < 0) {
                            // �׷��� ������ �����Ѵ�.
                            for (int z = 0; z < k; z++) {
                                restore[s + z] = ShortLeads[i][z];
                            }
                            break; // ���� short_read�� �Ѿ��.
                        }
                        else {
                            // ������ ���� ��ġ�� ���� �ʴٸ� �ٸ� ��ġ���� ������ ã�ƾ� �Ѵ�.
                            // ������ �󸶳� �ű����� badchar�� ����� ���� �������� �����Ѵ�.
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

    // ��� ���� ��ġ�� -1�� �ʱ�ȭ�Ѵ�.
    for (i = 0; i < 256; i++)
        badchar[i] = -1;

    // �׸��� ���� ���� ���� ������ ���� ��ġ�� �ٲ۴�.
    for (i = 0; i < size; i++)
        badchar[(int)pattern[i]] = i;
}


void BoyerMoore::make_gs_table(const string pattern, int* skip_tb) {
    const int p_size = pattern.size();

    int pattern_point = p_size;
    int suffix_point = pattern_point + 1;

    // ���̻�� ������ ���ڿ� üũ�ϴ� ���̺�
    int *suf_tb = new int[p_size + 1];
    suf_tb[pattern_point] = suffix_point;

    while (pattern_point > 0) {
        //cout<<'h'<<endl;
        // ���̻簡 ��ġ�ϴ� ���� ��� ��ġ�ϴ��� ī�����Ѵ�.
        while (suffix_point <= p_size && pattern[pattern_point - 1] != pattern[suffix_point - 1]) {
            if (skip_tb[suffix_point] == 0)
                skip_tb[suffix_point] = suffix_point - pattern_point;
            suffix_point = suf_tb[suffix_point];
        }

        // ���̻�� ������ �ܾ ���̻� �ε����� ����Ű���� ����
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