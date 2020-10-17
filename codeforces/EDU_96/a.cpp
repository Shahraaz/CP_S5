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

const int NAX = 1000 + 5, MOD = 1000000007;

int a[NAX], b[NAX], c[NAX];
int isSolved[NAX];
int res[NAX];

int solve(int x)
{
    if (x < 0)
        return 0;
    if (x == 0)
    {
        a[0] = 0;
        b[0] = 0;
        c[0] = 0;
        return true;
    }
    if (isSolved[x])
        return res[x];
    res[x] = 0;
    isSolved[x] = 1;
    if (solve(x - 3))
    {
        res[x] = 1;
        a[x] = a[x - 3] + 1;
        b[x] = b[x - 3];
        c[x] = c[x - 3];
    }
    if (solve(x - 5))
    {
        res[x] = 1;
        a[x] = a[x - 5];
        b[x] = b[x - 5] + 1;
        c[x] = c[x - 5];
    }
    if (solve(x - 7))
    {
        res[x] = 1;
        a[x] = a[x - 7];
        b[x] = b[x - 7];
        c[x] = c[x - 7] + 1;
    }
    return res[x];
}

void solveCase()
{
    int n;
    cin >> n;
    if (solve(n))
        cout << a[n] << ' ' << b[n] << ' ' << c[n] << '\n';
    else
        cout << -1 << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    memset(a, -1, sizeof a);
    memset(b, -1, sizeof b);
    memset(c, -1, sizeof c);
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
