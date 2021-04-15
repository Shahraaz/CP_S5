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

const string FIRST = "First";
const string SECOND = "Second";
auto solveCase(int n, const vector<int64_t> &a)
{
    // TODO: edit here
    if (n % 2)
        return SECOND;
    map<int, int> cnt;
    for (auto &x : a)
        cnt[x]++;
    for (auto &x : cnt)
    {
        if(x.second % 2)
            return FIRST;
    }
    return SECOND;
    
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
    int t, n;
    cin >> t;
    for (size_t i = 0; i < t; i++)
    {
        cin >> n;
        vector<int64_t> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        auto ans = solveCase(n, a);
        cout << ans << '\n';
    }

    return 0;
}