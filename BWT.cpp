#include "BWT.h"
#include <algorithm>
void BWT::Restore(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos) {

}

void BWT :: makeBWT(const string& ref){
  int length = ref.length();
  string origin = ref + "$";
  string double_origin = origin+origin;

  vector<string> fillTheRest;
  fillTheRest.push_back(origin);
  for(int i = 1 ; i < length; i++) {
    fillTheRest.push_back(double_origin.substr(length-i-1, length));
  }
  for(int i = 0 ; i < length; i++) {
    bwt += fillTheRest[i][length-1];
  }
  sort(bwt.begin(), bwt.end());
}