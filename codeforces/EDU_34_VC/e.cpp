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

const int NAX = 5000 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

// int dp[NAX];

void Solution::solveCase()
{
    int k, n;
    cin >> k >> n;
    set<string> s;

    auto check = [&](string &curr) -> bool {
        for (auto &it : s)
        {
            vector<int> diff;
            for (size_t i = 0; i < n; i++)
                if ((it[i] != curr[i]))
                    diff.pb(i);

            if (diff.size() == 0)
            {
                int ok = false;
                for (char c = 'a'; !ok && c <= 'z'; c++)
                {
                    int cnt = 0;
                    for (size_t i = 0; i < n; i++)
                        cnt += curr[i] == c;
                    ok = ok || cnt > 1;
                }
                if (!ok)
                    return false;
            }
            else if (diff.size() == 2)
            {
                if (it[diff[0]] != curr[diff[1]] || it[diff[1]] != curr[diff[0]])
                    return false;
            }
            else
                return false;
        }
        return true;
    };

    for (size_t i = 0; i < k; i++)
    {
        string str;
        cin >> str;
        s.insert(str);
    }
    if (s.size() == 1)
    {
        auto temp = *s.begin();
        swap(temp[0], temp[1]);
        cout << temp << '\n';
        return;
    }
    auto s1 = *s.begin();
    auto s2 = *next(s.begin());
    vector<int> diff;
    for (size_t i = 0; i < n; i++)
        if (s1[i] != s2[i])
            diff.pb(i);
    if (diff.size() == 1 || diff.size() > 4)
        cout << -1 << '\n';
    else
    {
        for (size_t i = 0; i < diff.size(); i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                auto r = s1;
                swap(r[diff[i]], r[j]);
                if (check(r))
                {
                    cout << r << '\n';
                    return;
                }
            }
        }
        cout << -1 << '\n';
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
