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
        string s;
        cin >> s;
        int m;
        cin >> m;
        while (m--)
        {
            int l, r, k;
            cin >> l >> r >> k;
            --l, --r;
            auto sNew = s;
            int sizeNew = r - l + 1;
            k %= sizeNew;
            for (size_t i = 0; i < sizeNew; i++)
                s[l + i] = sNew[l + (i - k + sizeNew) % sizeNew];
            db(sNew, s, l, r, k);
            // s = sNew;
        }
        cout << s << '\n';
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
