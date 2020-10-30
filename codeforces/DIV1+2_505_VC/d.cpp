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

const int NAX = 700 + 5, MOD = 1000000007;

int n;
vector<int> a;
bool dp[2][NAX][NAX];
bool isSolved[2][NAX][NAX];

int solve(int isRight, int lptr, int rptr)
{
    if (lptr > rptr)
        return 1;
    auto &ret = dp[isRight][lptr][rptr];
    if (isSolved[isRight][lptr][rptr])
        return ret;
    ret = false;
    isSolved[isRight][lptr][rptr] = 1;
    for (int ptr = lptr; ptr <= rptr; ptr++)
    {
        if (isRight && __gcd(a[lptr - 1], a[ptr]) > 1)
            if (solve(0, lptr, ptr - 1) && solve(1, ptr + 1, rptr))
                return ret = true;
        if (!isRight && __gcd(a[rptr + 1], a[ptr]) > 1)
            if (solve(0, lptr, ptr - 1) && solve(1, ptr + 1, rptr))
                return ret = true;
    }
    return ret;
}

void solveCase()
{
    cin >> n;
    a.resize(n);
    for (auto &x : a)
        cin >> x;
    for (int i = 0; i < n; i++)
        if (solve(0, 0, i - 1) && solve(1, i + 1, n - 1))
        {
            cout << "Yes\n";
            return;
        }
    cout << "No\n";
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
