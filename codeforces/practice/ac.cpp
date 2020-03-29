#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <math.h>
#include <assert.h>
#include <set>
#include <map>
#include <bitset>
#include <ctime>
#include <time.h>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <stack>
#include <ctype.h>
#include <numeric>
#include <sstream>
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <random>
#include <chrono>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
#define debug(name) DEBUG(#name, (name))
template<typename T>
void DEBUG(string label, T value) {
    cerr << "[" << label << " = " << value << "]\n";
}

vector<int> pref_func(const string &received){
    string rev = received;
    reverse(rev.begin(), rev.end());
    string cur = received + "." + rev;
    //debug(cur);
    vector<int> ret(cur.size());
    for(int i = 1; i < cur.size(); ++i){
        int j = ret[i - 1];
        while(j > 0 && cur[j] != cur[i]){
            j = ret[j - 1];
        }
        if(cur[j] == cur[i]){
            j++;
        }
        ret[i] = j;
    }
    return ret;
}
string longest(const string &cur){
    vector<int> pref = pref_func(cur);
    return cur.substr(0, pref[pref.size() - 1]);
}
void solve(){
    string s;
    cin >> s;
    int k = 0;
    for(int i = 0; i < s.size() / 2; ++i){
        if(s[i] != s[s.size() - 1 - i]){
            break;
        }
        k++;
    }
    int start = k;
    int end = s.size() - 1 - k;
    //debug(start);
    //debug(end);
    //debug(k);
    if(start >= end){
        cout << s << endl;
        return;
    }
    string middle = s.substr(start, end - start + 1);
    string rev_middle = middle;
    reverse(rev_middle.begin(), rev_middle.end());
    //debug(middle);
    //debug(rev_middle);

    string longest_middle = longest(middle);
    string longest_rev = longest(rev_middle);

    //debug(longest_middle);
    //debug(longest_rev);
    if(longest_middle.size() > longest_rev.size())swap(longest_middle, longest_rev);
    //debug(longest_middle);
    //debug(longest_rev);
    //debug(k);
    cout << s.substr(0, k) + longest_rev + s.substr(s.size() - k, k) << endl;
}
int main(int argv, char **argc){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    //string s;
    //while(cin >> s){
        //cout << longest(s) << endl;
    //}
    //return 0;
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
