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
    void solveCase()
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> pref[26];
        for (size_t i = 0; i < 26; i++)
        {
            pref[i].resize(n);
            for (size_t j = 0; j < n; j++)
            {
                pref[i][j] = s[j] == char('a' + i);
                if (j > 0)
                    pref[i][j] += pref[i][j - 1];
            }
        }
        auto getSum = [&](char idx, int start, int end) {
            if (start == 0)
                return pref[idx - 'a'][end];
            return pref[idx - 'a'][end] - pref[idx - 'a'][start - 1];
        };
        map<tuple<int, int, char>, int> mp;
        function<int(int, int, char)> check = [&](int start, int end, char c) -> int {
            if (start == end)
                return s[start] != c;
            if (mp.find({start, end, c}) != mp.end())
                return mp[{start, end, c}];
            int &ret = mp[{start, end, c}];
            int mid = (start + end) / 2;
            int sz = end - start + 1;
            int a = sz / 2 - getSum(c, start, mid) + check(mid + 1, end, c + 1);
            int b = sz / 2 - getSum(c, mid + 1, end) + check(start, mid, c + 1);
            return ret = min(a, b);
        };
        cout << check(0, n - 1, 'a') << '\n';
    }
};

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
