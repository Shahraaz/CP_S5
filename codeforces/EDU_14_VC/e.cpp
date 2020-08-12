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

const int NAX = 1e2 + 5, MOD = 1000000007;

ll arr[NAX];
// bool adj[NAX][NAX];
int **unit, **two, **zero;

int n;
struct Solution
{
    int **cross(int **a, int **b)
    {
        int **ret;
        ret = (int **)malloc(n * (sizeof(int *)));
        // vector<vector<int>> ret(n, vector<int>(n));
        for (size_t i = 0; i < n; i++)
        {
            ret[i] = (int *)malloc(n * (sizeof(int)));
            for (size_t j = 0; j < n; j++)
            {
                ret[i][j] = 0;
                for (size_t k = 0; k < n; k++)
                    ret[i][j] = (ret[i][j] + a[i][k] * 1LL * b[k][j]) % MOD;
            }
        }
        // for (size_t i = 0; i < n; i++)
        //     free(a[i]);
        // free(a);
        return ret;
    }
    int **expo(ll idx)
    {
        int **ret;
        // ret = (int **)malloc(n * (sizeof(int *)));
        // // vector<vector<int>> ret(n, vector<int>(n));
        // for (size_t i = 0; i < n; i++)
        // {
        //     ret[i] = (int *)malloc(n * (sizeof(int)));
        //     for (size_t j = 0; j < n; j++)
        //         ret[i][j] = 0;
        // }
        if (idx == 0)
            return unit;
        // if (idx == 1)
        //     return unit;
        // if (idx == 2)
        //     return two;
        auto temp = expo(idx / 2);
        ret = cross(temp, temp);
        if (idx & 1)
            ret = cross(ret, two);
        return ret;
    };
    Solution() {}
    void solveCase()
    {
        cin >> n;
        ll k;
        cin >> k;
        // unit.assign(n, vector<int>(n));
        // two.assign(n, vector<int>(n));
        unit = (int **)malloc(n * (sizeof(int *)));
        // zero = (int **)malloc(n * (sizeof(int *)));
        two = (int **)malloc(n * (sizeof(int *)));
        for (size_t i = 0; i < n; i++)
        {
            cin >> arr[i];
            unit[i] = (int *)malloc(n * (sizeof(int)));
            // zero[i] = (int *)malloc(n * (sizeof(int)));
            two[i] = (int *)malloc(n * (sizeof(int)));
            for (size_t j = 0; j < n; ++j)
                unit[i][j] = 0;
            unit[i][i] = 1;
        }
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < n; j++)
            {
                ll temp = arr[i] ^ arr[j];
                temp = __builtin_popcountll(temp);
                two[i][j] = (temp % 3) == 0;
            }
        auto ret = expo(k - 1);
        int res = 0;
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < n; j++)
                res = (res + 0LL + ret[i][j]) % MOD;
        cout << res << '\n';
    }
};

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
