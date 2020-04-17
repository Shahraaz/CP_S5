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

const int NAX = 3000 + 5, MOD = 998244353;

const int _n = 2e5 + 10;
vector<int> Fact(_n), Inv(_n);
const int kmod = 998244353;

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
    return power(x, kmod - 2);
}

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

int dp[NAX][NAX];
string s, t;
int n, m;

class Solution
{
private:
    int solve(int position, int suffixLen)
    {
        int prefLen = position - suffixLen;
        if (prefLen >= m)
        {
            int temp = power(2, n - prefLen);
            return temp;
        }
        int &ret = dp[position][suffixLen];
        if (ret >= 0)
            return ret;
        ret = 0;
        if (s[position] == t[prefLen])
            ret = add(ret, solve(position + 1, suffixLen));
        int pBack = m - suffixLen - 1;
        if (pBack >= 0 || s[position] == t[pBack])
            ret = add(ret, solve(position + 1, suffixLen + 1));
        // db(prefLen, remCnt, m, n);
        db(position, suffixLen, ret, '\n');
        return ret;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> s >> t;
        n = s.length();
        m = t.length();
        memset(dp, -1, sizeof dp);
        db(s, t);
        cout << solve(0, 0) << '\n';
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
