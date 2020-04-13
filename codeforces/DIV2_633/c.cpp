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

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (auto &x : a)
        {
            cin >> x;
        }
        vector<ll> prefmax(n);
        vector<ll> suffMin(n);
        prefmax[0] = a[0];
        for (size_t i = 1; i < n; i++)
            prefmax[i] = max(prefmax[i - 1], a[i]);
        suffMin[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; i--)
            suffMin[i] = min(suffMin[i + 1], a[i]);
        db(a, prefmax, suffMin);
        int res = 0;
        for (int i = n - 2; i >= 0; i--)
        {
            ll from = prefmax[i];
            ll to = suffMin[i + 1];
            db(to, from);
            db(bitset<40>(to), bitset<40>(from));
            if (from > to)
                for (int j = 0; j < 32; j++)
                {
                    to += 1LL << j;
                    if (to >= from)
                    {
                        res = max(res, j + 1);
                        break;
                    }
                }
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