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
const int NAX = 2e5 + 5, MOD = 1000000007;

const int kmod = 1000000007;

int mul(int a, int b, int mod = kmod)
{
    return (long long)a * b % mod;
}

int add(int a, int b, int mod = kmod)
{
    a += b;
    if (a >= mod)
        a -= mod;
    return a;
}

int sub(int a, int b, int mod = kmod)
{
    a -= b;
    if (a < 0)
        a += mod;
    return a;
}

int power(int base, int index, int mod = kmod)
{
    if (index == 0)
        return 1;
    int temp = power(base, index / 2, mod);
    temp = mul(temp, temp, mod);
    if (index & 1)
        temp = mul(temp, base, mod);
    return temp;
}

int mod_inv(int x, int mod = kmod)
{
    return power(x, mod - 2, mod);
}

// const int _n = 2e5 + 10;
// vector<int> Fact(_n), Inv(_n);

// void pre()
// {
//     Fact[0] = 1;
//     for (int i = 1; i < _n; ++i)
//         Fact[i] = mul(Fact[i - 1], i);
//     Inv[_n - 1] = mod_inv(Fact[_n - 1]);
//     for (int i = _n - 2; i >= 0; --i)
//         Inv[i] = mul(Inv[i + 1], (1 + i));
// }

// int ncr(int n, int r)
// {
//     if (n < 0 || r < 0 || n - r < 0)
//         return 0;
//     return mul(Fact[n], mul(Inv[r], Inv[n - r]));
// }

// int npr(int n, int r)
// {
//     if (n < 0 || r < 0 || n - r < 0)
//         return 0;
//     return mul(Fact[n], Inv[n - r]);
// }

struct matrix
{
    vector<vector<long long>> MAT;
    matrix() {}
    matrix(long long n, long long m)
    {
        MAT.resize(n, vector<long long>(m));
    }
};

matrix mul(const matrix &A, const matrix &B)
{
    int n = A.MAT.size(), m = B.MAT.size(), k = B.MAT[0].size();
    matrix X(n, k);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < k; ++j)
        {
            X.MAT[i][j] = 0;
            for (int k = 0; k < m; ++k)
                X.MAT[i][j] = add(X.MAT[i][j], mul(A.MAT[i][k], B.MAT[k][j]));
        }
    return X;
}

matrix unit(int n)
{
    matrix X(n, n);
    for (int i = 0; i < n; ++i)
        X.MAT[i][i] = 1;
    return X;
}

matrix power(const matrix &A, long long index)
{
    matrix temp;
    if (index == 0)
        return unit(A.MAT.size());
    temp = power(A, index / 2);
    temp = mul(temp, temp);
    if (index & 1)
        return mul(temp, A);
    return temp;
}

// constexpr int64_t MOD = 1000000007;
vector<int64_t> solveCase(int N, int M, int64_t K, vector<int64_t> A, const vector<int64_t> &X, const vector<int64_t> &Y)
{
    // TODO: edit here
    vector<vector<int>> adj(N);
    for (size_t i = 0; i < M; i++)
    {
        adj[X[i] - 1].pb(Y[i] - 1);
        adj[Y[i] - 1].pb(X[i] - 1);
    }
    if (M == 0)
        return A;
    // K = 1e5;
    matrix base(N, N);
    auto invm = mod_inv(M);
    auto inv2 = mod_inv(2);
    for (size_t i = 0; i < N; i++)
    {
        base.MAT[i][i] = M - adj[i].size();
        base.MAT[i][i] = add(base.MAT[i][i], mul(adj[i].size(), inv2));
        for (auto &x : adj[i])
            base.MAT[i][x] = 1;
        for (size_t j = 0; j < N; j++)
        {
            base.MAT[i][j] = mul(base.MAT[i][j], invm);
            db(i, j, mul(base.MAT[i][j], 2));
        }
        db(i, base.MAT[i]);
    }

    base = power(base, K);

    vector<int64_t> ret(N);
    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++)
            ret[i] = add(ret[i], mul(base.MAT[i][j], A[j]));

    // db(A);
    // db(next);
    return ret;
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main()
{
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    constexpr char endl = '\n';
    int64_t N, M;
    int64_t K;
    cin >> N;
    vector<int64_t> A(N);
    cin >> M;
    vector<int64_t> X(M), Y(M);
    cin >> K;
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i];
    }
    for (int i = 0; i < M; ++i)
    {
        cin >> X[i] >> Y[i];
    }
    auto ans = solveCase(N, M, K, A, X, Y);
    for (int i = 0; i < N; ++i)
    {
        cout << ans[i] << endl;
    }
    return 0;
}