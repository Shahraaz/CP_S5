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
    int a, b;
    cin >> a >> b;
    string s;
    cin >> s;
    vector<int> lens;
    db(a, b, s);
    for (size_t i = 0; i < s.size();)
    {
        if (s[i] == 'X')
        {
            ++i;
            continue;
        }
        int j = i + 1;
        while (j < s.size() && s[j] == '.')
            ++j;
        lens.pb(j - i);
        i = j;
    }
    if (lens.empty())
    {
        cout << "NO\n";
        return;
    }
    int idx = -1;
    int cnt = 0;
    for (auto &x : lens)
    {
        if (b <= x && x < a)
        {
            cout << "NO\n";
            return;
        }
        else if (a <= x && x < 2 * b)
            cnt++;
        else if (2 * b <= x)
        {
            if (idx == -1)
                idx = x;
            else
            {
                cout << "NO\n";
                return;
            }
        }
    }
    if (idx == -1)
    {
        if (cnt & 1)
            cout << "YES\n";
        else
            cout << "NO\n";
        return;
    }
    for (int rem1 = 0; idx - a - rem1 >= 0; rem1++)
    {
        int rem2 = idx - a - rem1;
        int ncnt = cnt;
        if (rem1 >= b + b || (b <= rem1 && rem1 < a))
            continue;
        if (rem2 >= b + b || (b <= rem2 && rem2 < a))
            continue;
        if (rem1 >= a)
            ++ncnt;
        if (rem2 >= a)
            ++ncnt;
        if (ncnt % 2 == 0)
        {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
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
