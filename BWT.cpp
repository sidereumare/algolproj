#include "BWT.h"

int BWT::search(const string& target)
{

    return -1;
}

void BWT::Restore(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos) {
    
    makeBWT(ref);
    
    //복원한 문자열이 들어갈 공간 미리 지정
    restore.assign(ref.length(), 'N');

    for (const auto& l : ShortLeads) {
        int pos = -1;
        pos = search(l);
        if (pos == -1) {
            continue;
        }

        for (int i = 0; i<l.length(); i++) {
            restore[pos + i] = l[i];
        }
    }

    cout << restore << '\n';
    for (auto t : originpos) {
        cout << t << '\n';
    }

}

void BWT :: makeBWT(const string& ref){
    //입력: ref문자열을 받아 BWT문자열을 생성
    // add $ 
    string origin = ref + "$";
    int length = origin.length();
    string double_origin = origin+origin;

    vector<pair<string, int>> fillTheRest;
  
    // fill the rest
    for(int i = 0 ; i < length; i++) {
        fillTheRest.push_back(make_pair(double_origin.substr(length-(i+1), length), length-(i+1)));
    // print for debugging
    // cout << fillTheRest[i].second <<", " << fillTheRest[i].first << endl;
    }
    // sort
    sort(fillTheRest.begin(), fillTheRest.end());
    // make bwt& first
    for(int i = 0 ; i < length; i++) {
        bwt += (fillTheRest[i].first)[length-1];
        first += (fillTheRest[i].first)[0];
        originpos.push_back(fillTheRest[i].second);
    }

    int chcount[4] = { 0,0,0,0 };//상대위치 검색용, 각각 ACGT
    for (int i = 0; i < length; i++) {
        if (bwt[i] == 'A') {
            postofirst.push_back(chcount[0]);
            chcount[0]++;
        }
        else if (bwt[i] == 'C') {
            postofirst.push_back(chcount[0]);
            chcount[1]++;
        }
        else if (bwt[i] == 'G') {
            postofirst.push_back(chcount[0]);
            chcount[2]++;
        }
        else {
            postofirst.push_back(chcount[0]);
            chcount[3]++;
        }
    }

    char before = '$';
    int pos = 0;
    for (int i = 1; i < length; i++) {
        if (before != first[i]) {
            posstart[pos++] = i;
            before = first[i];
        }
    }
}