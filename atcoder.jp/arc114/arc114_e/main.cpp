#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

constexpr int64_t MOD = 998244353;
int64_t solveCase(int n, const vector<int64_t> & a) {
    // TODO: edit here
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main() 
{
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    constexpr char endl = '\n';
    // failed to analyze input format
    // TODO: edit here
    int n;
    cin >> n;
    vector<int64_t> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    auto ans = solveCase(n, a);
    cout << ans << endl;
    return 0;
}