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
    string str;
    cin >> str;
    int n = str.size();
    str = "$" + str;
    vector<vector<int>> cnt(n + 1, vector<int>(26));
    for (size_t i = 1; i <= n; i++)
    {
        cnt[i] = cnt[i - 1];
        cnt[i][str[i] - 'a']++;
    }
    int q;
    cin >> q;
    for (size_t i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        int ctr = 0;
        for (size_t j = 0; j < 26; j++)
            ctr += (cnt[r][j] - cnt[l - 1][j]) > 0;
        if (l == r || (ctr >= 3) || (str[l] != str[r]))
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}