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

struct Solution
{
    Solution() {}
    void solveCase();
};

void Solution::solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (size_t i = 1; i <= n; i++)
        cin >> a[i];
    const int SQRT = 600;
    vector<vector<int>> vecc(SQRT);
    for (size_t k1 = 1; k1 < SQRT; k1++)
    {
        vecc[k1].resize(n + 1);
        for (int i = n; i >= 1; i--)
        {
            int next = i + a[i] + k1;
            if (next > n)
                vecc[k1][i] = 1;
            else
                vecc[k1][i] = 1 + vecc[k1][next];
        }
    }
    int q;
    cin >> q;
    while (q--)
    {
        int p, k;
        cin >> p >> k;
        if (k < SQRT)
            cout << vecc[k][p] << '\n';
        else
        {
            int ctr = 0;
            while (p <= n)
            {
                p = p + a[p] + k;
                ++ctr;
            }
            cout << ctr << '\n';
        }
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
