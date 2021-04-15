#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    vector<vector<int>> cnt(26, vector<int>(n));
    for (size_t i = 0; i < n; i++)
    {
        cnt[str[i] - 'a'][i]++;
    }
    for (size_t i = 0; i < 26; i++)
        for (size_t j = 0; j + 1 < n; j++)
            cnt[i][j + 1] += cnt[i][j];

    int m;
    cin >> m;
    for (size_t i = 0; i < m; i++)
    {
        string q;
        cin >> q;
        vector<int> freq(26);
        for (auto &x : q)
            freq[x - 'a']++;
        int res = 0;
        for (size_t i = 0; i < 26; i++)
        {
            if (freq[i])
            {
                auto idx = lower_bound(all(cnt[i]), freq[i]) - cnt[i].begin() + 1;
                db(i, idx, freq[i]);
                res = max(res, (int)idx);
            }
        }
        cout << res << '\n';
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