#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(const string& in, int fcount[26], const set<string>& dict,
    string& curr, int pos, int ftotal, int free, set<string>& results);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
  set<string> results;
  string curr = in;
  
  int fcount[26] = {0};
  int ftotal = 0;
  for (int i = 0; i < (int)floating.length(); i++) {
      fcount[floating[i] - 'a']++;
      ftotal++;
  }
  
  int free = 0;
  for (int i = 0; i < (int)in.length(); i++) {
      if (in[i] == '-') {
          free++;
      }
  }
  
  wordleHelper(in, fcount, dict, curr, 0, ftotal, free, results);
  return results;
}

// Define any helper functions here

void wordleHelper(const string& in, int fcount[26], const set<string>& dict,
    string& curr, int pos, int ftotal, int free, set<string>& results)
{
    if (pos == (int)in.length()) {
        if (ftotal == 0 && dict.find(curr) != dict.end()) {
            results.insert(curr);
        }
        return;
    }

    if (in[pos] != '-') {
        curr[pos] = in[pos];
        wordleHelper(in, fcount, dict, curr, pos + 1, ftotal, free, results);
        return;
    }
    
    if (ftotal > free) {
        return;
    }

    for (char c = 'a'; c <= 'z'; c++) {
        int idx = c - 'a';
        if (fcount[idx] > 0) {
            fcount[idx]--;
            curr[pos] = c;
            wordleHelper(in, fcount, dict, curr, pos + 1, ftotal - 1, free - 1, results);
            fcount[idx]++;
        } else if (free > ftotal) {
            curr[pos] = c;
            wordleHelper(in, fcount, dict, curr, pos + 1, ftotal, free - 1, results);
        }
    }
}