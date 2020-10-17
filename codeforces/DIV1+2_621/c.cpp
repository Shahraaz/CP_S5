// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    string s;
    cin >> s;
    if (s.length() == 1)
    {
        cout << 1 << '\n';
        return;
    }
    vector<int> poses[26];
    for (size_t i = 0; i < s.size(); i++)
        poses[s[i] - 'a'].pb(i);
    ll res = 0;
    for (size_t a = 0; a < 26; a++)
    {
        res = max(res, (ll)poses[a].size());
        for (size_t b = 0; b < 26; b++)
        {
            ll tempRes = 0;
            for (auto &one : poses[a])
            {
                auto it = poses[b].end() - upper_bound(all(poses[b]), one);
                tempRes += it;
            }
            res = max(res, tempRes);
        }
    }
    cout << res << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
