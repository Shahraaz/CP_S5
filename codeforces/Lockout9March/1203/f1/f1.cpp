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
    ll curr_r = 0;
    cin >> curr_r;
    vector<pair<ll, ll>> gain, loss;
    for (size_t i = 0; i < n; i++)
    {
        ll a, b;
        cin >> a >> b;
        if (b >= 0)
            gain.pb({a, b});
        else
        {
            a = max(a, -b);
            loss.pb({a + b, b});
        }
    }
    sort(all(gain));
    sort(all(loss));
    db(gain);
    for (auto &x : gain)
    {
        ll a = x.first, b = x.second;
        db(curr_r, a, b);
        if (curr_r >= a)
        {
            curr_r += b;
        }
        else
        {
            cout << "NO\n";
            return;
        }
    }
    db(loss);
    reverse(all(loss));
    for (auto &x : loss)
    {
        ll a_b = x.first, b = x.second;
        ll a = a_b - b;
        db(curr_r, a, b);
        if (curr_r >= a)
        {
            curr_r += b;
        }
        else
        {
            cout << "NO\n";
            return;
        }
        if (curr_r < 0)
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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