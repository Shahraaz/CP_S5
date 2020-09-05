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

const int NAX = 5000 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

// int dp[NAX];

void Solution::solveCase()
{
    int k, n;
    cin >> k >> n;
    vector<string> s(k);
    string hash;
    for (auto &x : s)
    {
        cin >> x;
        auto y = x;
        sort(all(y));
        if (hash.size())
        {
            if (y != hash)
            {
                cout << -1 << '\n';
                return;
            }
        }
        else
            hash = y;
    }
    if (k == 1)
    {
        cout << s[0] << '\n';
        return;
    }
    string sstr;
    for (size_t i = 0; i < n; i++)
        if (s[0][i] != s[1][i])
            sstr.pb('?');
        else
            sstr.pb(s[0][i]);
    function<void(int)> solve = [&](int pos) -> void {
        if (pos == n)
        {
            db(sstr);
            for (size_t i = 0; i < k; i++)
            {
                int cnt = 0;
                for (size_t j = 0; j < n; j++)
                    cnt += sstr[j] != s[i][j];
                if (cnt == 0 || cnt == 2)
                    continue;
                return;
            }
            auto y = sstr;
            sort(all(y));
            db(y, hash, sstr);
            if (y == hash)
            {
                cout << sstr << '\n';
                exit(0);
            }
            return;
        }
        if (sstr[pos] == '?')
        {
            for (char c = 'a'; c <= 'z'; c++)
            {
                sstr[pos] = c;
                solve(pos + 1);
                sstr[pos] = '?';
            }
        }
        else
        {
            solve(pos + 1);
        }
    };
    db(sstr);
    solve(0);
    sstr = "";
    if (k > 2)
    {
        for (size_t i = 0; i < n; i++)
            if (s[0][i] != s[2][i])
                sstr.pb('?');
            else
                sstr.pb(s[0][i]);
        solve(0);
    }
    if (k > 2)
    {
        for (size_t i = 0; i < n; i++)
            if (s[1][i] != s[2][i])
                sstr.pb('?');
            else
                sstr.pb(s[0][i]);
        solve(0);
    }
    if (k > 3)
    {
        for (size_t i = 0; i < n; i++)
            if (s[1][i] != s[3][i])
                sstr.pb('?');
            else
                sstr.pb(s[0][i]);
        solve(0);
    }
    cout << -1 << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
