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

void solveCase()
{
    string str;
    cin >> str;
    int n = str.size();
    vector<int> res;
    for (size_t i = 0; i + 2 < n; i++)
    {
        if (str.substr(i, 3) == "one")
            res.pb(i + 1);
        else if (str.substr(i, 3) == "two")
        {
            if (str.substr(i + 2, 3) == "one")
            {
                res.pb(i + 2);
                i = i + 2;
            }
            else
            {
                res.pb(i + 1);
            }
        }
    }
    cout << res.size() << '\n';
    for (auto &&x : res)
        cout << x + 1 << ' ';
    cout << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
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
