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
    int n, k;
    cin >> n >> k;
    string str;
    cin >> str;
    for (size_t i = 0; i < k; i++)
    {
        vector<int> cnt(3);
        for (size_t j = i; j < n; j += k)
        {
            if (str[j] == '?')
                cnt[2]++;
            else if (str[j] == '0')
                cnt[0]++;
            else if (str[j] == '1')
                cnt[1]++;
        }
        if (cnt[0] > 0 && cnt[1] > 0)
        {
            cout << "NO\n";
            return;
        }
        if (cnt[0] > 0)
        {
            for (size_t j = i; j < n; j += k)
                str[j] = '0';
        }
        else if (cnt[1] > 0)
        {
            for (size_t j = i; j < n; j += k)
                str[j] = '1';
        }
    }
    vector<int> cnt(3);
    for (size_t i = 0; i < k; i++)
    {
        if (str[i] == '?')
            cnt[2]++;
        else if (str[i] == '0')
            cnt[0]++;
        else if (str[i] == '1')
            cnt[1]++;
    }
    for (size_t ctr = 0; ctr <= cnt[2]; ctr++)
    {
        int rem = cnt[2] - ctr;
        if (cnt[0] + ctr == cnt[1] + rem)
        {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
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
