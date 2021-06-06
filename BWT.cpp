#include "BWT.h"

int BWT::search(const string& target ,const vector<int>& snipPos)
{
    auto func = [&](const string& target, int start) {
        int current = start;
        for (int i = target.length() - 2; i > 0 ; i--) {
            if (bwt[current] == '$') {
                return false;
            }
            if (target[i] != bwt[current] && !binary_search(snipPos.begin(), snipPos.end(), originpos[current])) {
                return false;
            }
            current = postofirst[current];
        }
        return true;
    };

    //탐색 범위 지정
    int start = 0;
    int end = 0;
    int target_l = target.length() - 1;
    if (target[target_l] == 'A') {
        start = posstart[0];
        end = posstart[1];
    }
    else if (target[target_l] == 'C') {
        start = posstart[1];
        end = posstart[2];
    }
    else if (target[target_l] == 'G') {
        start = posstart[2];
        end = posstart[3];
    }
    else{
        start = posstart[3];
        end = target_l + 1;
    }
    
    
    for (int i = start; i < end; i++) {
        if (func(target, i)) {
            return originpos[i] - target.length() + 1;
        }
    }
    return -1;
}

void BWT::Restore(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos) {
    
    makeBWT(ref);
    
    //복원한 문자열이 들어갈 공간 미리 지정
    restore.assign(ref.length(), 'N');
    


    auto func = [this, &ShortLeads, &snipPos](int start) {
        for (int i = start; i < ShortLeads.size(); i += 10) {
            int pos = -1;
            pos = search(ShortLeads[i], snipPos);
            if (pos == -1) {
                _mux.lock();
                misRead.push_back(ShortLeads[i]);
                _mux.unlock();
                continue;
            }

            for (int j = 0; j < ShortLeads[i].length(); j++) {
                restore[pos + j] = ShortLeads[i][j];
            }
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

void BWT :: makeBWT(const string& ref){
    //입력: ref문자열을 받아 BWT문자열을 생성
    // add $ 
    string origin = ref + "$";
    int length = origin.length();
    string double_origin = origin+origin;

    vector<pair<string, int>> *fillTheRest = new vector<pair<string, int>>();
  
    // fill the rest
    for(int i = 0 ; i < length; i++) {
        fillTheRest->push_back(make_pair(double_origin.substr(length-(i+1), length), length-(i+1)));
    // print for debugging
    // cout << fillTheRest[i].second <<", " << fillTheRest[i].first << endl;
    }
    // sort
    sort(fillTheRest->begin(), fillTheRest->end());
    // make bwt& first
    for(int i = 0 ; i < length; i++) {
        bwt += ((*fillTheRest)[i].first)[length-1];
        first += ((*fillTheRest)[i].first)[0];
        originpos.push_back((*fillTheRest)[i].second);
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
    for (int i = 0; i < length; i++) {
        if (bwt[i] == 'A') {
            postofirst[i] += posstart[0];
        }
        else if (bwt[i] == 'C') {
            postofirst[i] += posstart[1];
        }
        else if (bwt[i] == 'G') {
            postofirst[i] += posstart[2];
        }
        else {
            postofirst[i] += posstart[3];
        }
    }


    char before = '$';
    int pos = 0;
    for (int i = 0; i < 4; i++) {
        posstart[i] = ref.length() + 1;
    }
    for (int i = 1; i < length; i++) {
        if (before != first[i]) {
            posstart[pos++] = i;
            before = first[i];
        }
    }
}