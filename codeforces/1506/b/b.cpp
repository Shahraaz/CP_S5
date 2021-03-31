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

void solveCase()
{
    int n, k;
    cin >> n >> k;
    string str;
    cin >> str;
    vector<int> min_for_now(n, MOD);
    auto idx = find(all(str), '*') - str.begin();
    // assert(idx != str.end());
    min_for_now[idx] = 0;
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        if (str[i] == '.')
            continue;
        int now = min_for_now[i];
        res = now;
        for (int j = i + 1; j < n; j++)
        {
            if (j - i > k)
                break;
            if (str[j] == '.')
                continue;
            min_for_now[j] = min(min_for_now[j], now + 1);
        }
    }
    cout << res+1 << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}