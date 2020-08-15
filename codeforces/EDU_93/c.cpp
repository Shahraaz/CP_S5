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
        string a;
        cin >> a;
        vector<ll> A(n);
        map<int, int> mp;
        for (int i = 0; i < n; i++)
        {
            A[i] = a[i] - '0';
            if (i > 0)
                A[i] += A[i - 1];
        }
        for (int i = 0; i < n; i++)
            mp[A[i] - i]++;
        ll res = 0;
        for (int i = 0; i < n; i++)
        {
            int temp = -i + 1;
            if (i > 0)
                temp += A[i - 1];
            res += mp[temp];
            db(i, temp, mp[temp], mp);
            mp[A[i] - i]--;
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
