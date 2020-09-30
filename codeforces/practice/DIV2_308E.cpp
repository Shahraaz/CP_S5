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

int n;
string s;

ll solve(int start, int end)
{
    pair<ll, ll> temp;
    temp.f = s[start] - '0';
    for (size_t i = start + 1; i < end; i += 2)
    {
        if (s[i] == '*')
            temp.f *= s[i + 1] - '0';
        else
        {
            temp.s += temp.f;
            temp.f = s[i + 1] - '0';
        }
    }
    ll mid = temp.f + temp.s;
    start--;
    end++;
    db(start, end, mid);
    temp.f = s[0] - '0';
    temp.s = 0;
    ll res = 0;
    bool first = true;
    for (size_t i = 1; i < n; i += 2)
    {
        db(i, mid, temp, first);
        if (i >= start && first)
        {
            first = false;
            temp.f = temp.f * mid;
            i = end - 2;
        }
        else if (s[i] == '*')
            temp.f *= s[i + 1] - '0';
        else
        {
            temp.s += temp.f;
            temp.f = s[i + 1] - '0';
        }
    }
    res += temp.f + temp.s;
    db(start, end, mid, res);
    return res;
}

void solveCase()
{
    // cin >> n;
    cin >> s;
    s = "1*" + s + "*1";
    n = s.length();
    db(s, n);
    vector<int> poses;
    for (size_t i = 1; i < n; i += 2)
        if (s[i] == '*')
            poses.pb(i);
    ll res = 0;
    for (size_t i = 0; i < poses.size(); i++)
        for (int j = i + 1; j < poses.size(); j++)
            res = max(res, solve(poses[i] + 1, poses[j] - 1));
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
