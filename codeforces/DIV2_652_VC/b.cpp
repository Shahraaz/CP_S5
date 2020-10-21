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
    int n;
    string s;
    cin >> n;
    cin >> s;
    deque<pair<char, int>> Dq, pref, suff;
    for (size_t i = 0; i < n;)
    {
        int j = i;
        while (j < n && s[j] == s[i])
            ++j;
        Dq.pb({s[i], j - i});
        i = j;
    }
    db(Dq);
    if (Dq.size() && Dq.front().f == '0')
    {
        pref.pb(Dq.front());
        Dq.pop_front();
    }
    if (Dq.size() && Dq.back().f == '1')
    {
        suff.pb(Dq.back());
        Dq.pop_back();
    }
    if (Dq.size())
        pref.pb({'0', 1});
    for (auto &x : pref)
    {
        while (x.s--)
        {
            cout << x.f;
        }
    }
    for (auto &x : suff)
    {
        while (x.s--)
        {
            cout << x.f;
        }
    }
    cout << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
