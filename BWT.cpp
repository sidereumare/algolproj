#include "BWT.h"

void BWT::Restore(const vector<string>& ShortLeads, const string& ref, const vector<int>& snipPos) {
    // fix error..
}

void BWT :: makeBWT(const string& ref){
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
  // make bwt 
  for(int i = 0 ; i < length; i++) {
    bwt += (fillTheRest[i].first)[length-1];
    // print for debugging
    // cout << fillTheRest[i].second << ", " << fillTheRest[i].first << endl;
  }
  // print to debugging
  //cout << bwt << endl;
}