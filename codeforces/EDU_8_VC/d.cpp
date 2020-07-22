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

int dp[2005][2005][2][2];
int m, d;

int add(int a, int b)
{
    a += b;
    if (a >= MOD)
        a -= MOD;
    return a;
}

int sub(int a, int b)
{
    a -= b;
    if (a < 0)
        a += MOD;
    return a;
}

struct Solution
{
    Solution() {}
    void solveCase()
    {
        cin >> m >> d;
        string a, b;
        cin >> a >> b;
        struct solve
        {
            string s;
            int res = 0;
            int solve_dp(int pos, int rem, int hogya, int chance)
            {
                if (pos == s.size())
                    return rem % m == 0;
                int &ret = dp[pos][rem][hogya][chance];
                if (ret >= 0)
                    return ret;
                int start = 9;
                if (hogya)
                    start = s[pos] - '0';
                ret = 0;
                if (chance)
                {
                    if (d <= start)
                        ret = add(ret, solve_dp(pos + 1, (rem * 10 + d) % m, hogya || (d < start), chance));
                }
                else
                {
                    for (int i = start; i >= 0; i--)
                        if (i != d)
                            ret = add(ret, solve_dp(pos + 1, (rem * 10 + i) % m, hogya || (i < start), 1 - chance));
                }
                return ret;
            }
            solve(string s)
            {
                this->s = s;
                memset(dp, -1, sizeof dp);
                res = 0;
                db(s);
                for (int i = 1; i <= s[0] - '0'; i++)
                {
                    if (i == d)
                        continue;
                    res = add(res, solve_dp(1, i % m, i == (s[0] - '0'), 1));
                    db(i, res);
                }
                db(res);
                for (size_t j = 1; j < s.size(); j++)
                {
                    for (int i = 1; i <= 9; i++)
                    {
                        if (i == d)
                            continue;
                        res = add(res, solve_dp(j + 1, i % m, 0, 1));
                    }
                    db(j, res);
                }
                auto N = to_string(0);
                bool b = true;
                for (size_t j = 0; j < N.size(); j++)
                {
                    if (j % 2 == 0)
                    {
                        if (N[j] == '0' + d)
                            b = false;
                    }
                    else
                    {
                        if (N[j] != '0' + d)
                            b = false;
                    }
                }
                res += b;
#ifdef LOCAL
                auto n = stoll(s);
                int brute = 0;
                for (size_t i = 0; i <= n; i++)
                {
                    if (i % m)
                        continue;
                    auto N = to_string(i);
                    bool b = true;
                    for (size_t j = 0; j < N.size(); j++)
                    {
                        if (j % 2 == 0)
                        {
                            if (N[j] == '0' + d)
                                b = false;
                        }
                        else
                        {
                            if (N[j] != '0' + d)
                                b = false;
                        }
                    }
                    if (b)
                        cout << i << ' ';
                    brute += b;
                }
                cout << '\n';
                db(s, brute, res);
#endif
            }
        };
        auto sub = [&](string a) -> string {
            if (count(all(a), '0') == a.size())
                return "";
            reverse(all(a));
            bool carry = true;
            for (size_t i = 0; i < a.size(); i++)
            {
                int num = a[i] - '0';
                if (carry)
                {
                    if (num > 0)
                    {
                        num--;
                        carry = false;
                    }
                    else
                    {
                        num = 9;
                    }
                }
                a[i] = num + '0';
            }
            while (a.size() > 1 && a.back() == '0')
                a.pop_back();
            reverse(all(a));
            return a;
        };
        db(m, d);
        auto res = solve(b).res;
        // db(res, b);
        db(a, sub(a));
        a = sub(a);
        if (a.size() > 0)
        {
            auto temp = solve(a).res;
            // db(a, temp);
            res = (res - temp + MOD) % MOD;
        }
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
