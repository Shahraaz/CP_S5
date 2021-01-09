#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 998244353;

ll ocnt = 0, ecnt = 0;

vector<vector<ll>> mul(vector<vector<ll>> &a, vector<vector<ll>> &b)
{
    vector<vector<ll>> ret(2, vector<ll>(2));
    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 2; j++)
        {
            ret[i][j] = 0;
            for (size_t k = 0; k < 2; k++)
                ret[i][j] = (ret[i][j] + a[i][k] * b[k][j]) % MOD;
        }
    return ret;
}

vector<vector<ll>> expo(ll idx)
{
    vector<vector<ll>> ret(2, vector<ll>(2));
    ret[0][0] = ret[1][1] = 1;

    vector<vector<ll>> A(2, vector<ll>(2));
    A[0][0] = A[1][1] = ecnt;
    A[0][1] = A[1][0] = ocnt;

    db(idx);

    while (idx)
    {
        db(idx, A);
        db(ret);
        if (idx & 1)
            ret = mul(ret, A);
        A = mul(A, A);
        idx /= 2;
    }

    db(ret);
    return ret;
}

void solveCase()
{
    ll n, m, L, R;
    cin >> n >> m >> L >> R;
    if ((R - L + 1) & 1)
    {
        if (L & 1)
            ocnt++;
        else
            ecnt++;
        ++L;
    }
    if (L <= R)
    {
        ocnt += (R - L + 1) / 2;
        ecnt += (R - L + 1) / 2;
        ocnt %= MOD;
        ecnt %= MOD;
    }
    db(ocnt, ecnt);
    vector<vector<ll>> matrix(2, vector<ll>(2));
    matrix[0][0] = matrix[1][1] = 1;
    matrix = expo(n * m);
    if ((n * m) & 1)
        cout << (matrix[0][0] + matrix[1][0]) % MOD << '\n';

    else
        cout << matrix[0][0] << '\n';
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