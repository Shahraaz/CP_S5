#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n, k, m;
    cin >> n >> k >> m;
    vector<vector<int>> vecc(m);
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        vecc[x % m].pb(x);
    }
    db(vecc);
    for (auto &x : vecc)
    {
        if (x.size() >= k)
        {
            cout << "Yes\n";
            for (size_t i = 0; i < k; i++)
                cout << x[i] << ' ';
            cout << '\n';
            return;
        }
    }
    cout << "No\n";
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
        solveCase();
    return 0;
}