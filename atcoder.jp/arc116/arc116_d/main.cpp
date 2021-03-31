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
// const int NAX = 2e5 + 5, MOD = 1000000007;

constexpr int64_t MOD = 998244353, NAX = 5001;

const int kmod = MOD;

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

const int _n = 5000 + 10;
vector<int> Fact(_n), Inv(_n);

void pre()
{
    Fact[0] = 1;
    for (int i = 1; i < _n; ++i)
        Fact[i] = mul(Fact[i - 1], i);
    Inv[_n - 1] = mod_inv(Fact[_n - 1]);
    for (int i = _n - 2; i >= 0; --i)
        Inv[i] = mul(Inv[i + 1], (1 + i));
}

int ncr(int n, int r)
{
    if (n < 0 || r < 0 || n - r < 0)
        return 0;
    return mul(Fact[n], mul(Inv[r], Inv[n - r]));
}

int npr(int n, int r)
{
    if (n < 0 || r < 0 || n - r < 0)
        return 0;
    return mul(Fact[n], Inv[n - r]);
}

// int dp[13][NAX][NAX];
int dp[13][NAX];

int solve(int idx, int sum, int x, const int N)
{
    if (sum < 0)
        return 0;
    if (idx == 13)
        return sum == 0 && x == 0;
    auto &ret = dp[idx][sum];
    if (ret >= 0)
        return ret;
    ret = 0;
    if ((sum >> idx & 1) != (x >> idx & 1))
        return ret;
    int xnext = x & (x & (1 << idx));
    for (size_t cnt = x & 1; cnt <= N; cnt++)
    {
        auto temp = ncr(N, cnt);
        temp = mul(temp, solve(idx + 1, sum - cnt * (1 << idx), xnext, N));
        ret = add(ret, temp);
    }
    db(idx, sum, x, N, ret);
    return ret;
}

int64_t solveCase(int64_t N, int64_t M)
{
    pre();
    memset(dp, -1, sizeof dp);
    return solve(0, M, 0, N);

    // vector<vector<int>> dp(NAX, vector<int>(NAX));
    // dp[0][0] = 1;
    // for (size_t idx = 0; idx < 14; idx++)
    // {
    //     vector<vector<int>> dpb(NAX, vector<int>(NAX));
    //     for (int x = 0; x <= M; x++)
    //     {
    //         for (int s = 0; s <= M; s++)
    //             for (size_t cnt = 0; cnt <= N; cnt++)
    //             {
    //                 int snew = s + cnt * (1 << idx);
    //                 if (snew > M)
    //                     break;
    //                 int xnew = x + (cnt & 1) * (1 << idx);
    //                 dpb[snew][xnew] = add(dpb[snew][xnew], mul(ncr(N, cnt), dp[x][s]));
    //             }
    //         db(idx,x);
    //     }
    //     // db(idx);
    //     // db(dp);
    //     dp = dpb;
    // }
    // return dp[M][0];
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
    cin >> N >> M;
    auto ans = solveCase(N, M);
    cout << ans << endl;
    return 0;
}