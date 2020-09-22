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

vector<int> p(100);
vector<int> used(100 + 1);
vector<int> Nums[2];
vector<pair<int, int>> gaps;
int dp[101][101][101];
int n;

int solve(int pos, int evenRem, int oddRem)
{
    if (evenRem < 0 || oddRem < 0)
        return 1000;
    if (pos == gaps.size())
        return (evenRem == 0 && oddRem == 0) ? 0 : 1000;
    int &ret = dp[pos][evenRem][oddRem];
    if (ret >= 0)
        return ret;
    ret = 1000;
    int len = gaps[pos].s - gaps[pos].f + 1;

    // all even
    int temp = 0;
    if (gaps[pos].f - 1 >= 0)
        temp += p[gaps[pos].f - 1] & 1;
    if (gaps[pos].s + 1 < n)
        temp += p[gaps[pos].s + 1] & 1;
    // db("even", temp);
    ret = min(ret, temp + solve(pos + 1, evenRem - len, oddRem));

    // all odd
    temp = 0;
    if (gaps[pos].f - 1 >= 0)
        temp += 1 - (p[gaps[pos].f - 1] & 1);
    if (gaps[pos].s + 1 < n)
        temp += 1 - (p[gaps[pos].s + 1] & 1);
    // db("odd", temp);
    ret = min(ret, temp + solve(pos + 1, evenRem, oddRem - len));

    for (int i = 0; i < len; i++)
    {
        //odd Followed By Even
        temp = 0;
        if (gaps[pos].f - 1 >= 0)
            temp += 1 - (p[gaps[pos].f - 1] & 1);
        if (gaps[pos].s + 1 < n)
            temp += p[gaps[pos].s + 1] & 1;
        // db("odd", i, "even", len - i, temp);
        ret = min(ret, 1 + temp + solve(pos + 1, evenRem - len + i, oddRem - i));

        //Even Followed By odd
        temp = 0;
        if (gaps[pos].f - 1 >= 0)
            temp += p[gaps[pos].f - 1] & 1;
        if (gaps[pos].s + 1 < n)
            temp += 1 - (p[gaps[pos].s + 1] & 1);
        // db("odd", len - i, "even", i, temp);
        ret = min(ret, 1 + temp + solve(pos + 1, evenRem - i, oddRem - len + i));
    }
    db(pos, gaps[pos], evenRem, oddRem, ret);
    return ret;
}

void solveCase()
{
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        cin >> p[i];
        used[p[i]]++;
    }
    int def = 0;
    for (size_t i = 0; i < n; ++i)
    {
        if (p[i] > 0)
        {
            int l = i, r = i;
            int temp = 0;
            while (r + 1 < n && p[r + 1] > 0)
            {
                temp += (p[r] & 1) != (p[r + 1] & 1);
                ++r;
            }
            i = r;
            def += temp;
        }
        else
        {
            int l = i, r = i;
            while (r + 1 < n && p[r + 1] == 0)
                ++r;
            gaps.pb({l, r});
            i = r;
        }
    }
    for (size_t i = 1; i <= n; i++)
    {
        if (used[i] == 0)
            Nums[i & 1].pb(i);
    }
    db(gaps);
    memset(dp, -1, sizeof dp);
    auto res = solve(0, Nums[0].size(), Nums[1].size());
    cout << def + res << '\n';
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
