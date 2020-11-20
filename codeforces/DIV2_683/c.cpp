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
    int n;
    cin >> n;
    ll w;
    cin >> w;
    vector<ll> W(n);
    vector<int> idexes;
    for (size_t i = 0; i < n; ++i)
        cin >> W[i];
    ll sum = 0;
    for (size_t i = 0; i < n; ++i)
    {
        if (W[i] > w)
            continue;
        if (2 * W[i] >= w)
        {
            cout << 1 << '\n'
                 << i + 1 << '\n';
            return;
        }
        sum += W[i];
        idexes.pb(i + 1);
        if (2 * sum >= w)
        {
            cout << idexes.size() << '\n';
            for (auto &x : idexes)
            {
                cout << x << ' ';
            }
            cout << '\n';
            return;
        }
    }
    cout << -1 << '\n';
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
        solveCase();
    return 0;
}