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

int n;
ll p, t[NAX], ans[NAX];

int bit[NAX];

void add(int idx, int x)
{
    for (; idx < NAX; idx += (idx & -idx))
        bit[idx] += x;
}

int query(int idx)
{
    int ret = 0;
    for (; idx; idx -= (idx & -idx))
        ret += bit[idx];
    return ret;
}

void solveCase()
{
    cin >> n >> p;
    for (size_t i = 1; i <= n; i++)
        cin >> t[i];
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> boil, star;
    priority_queue<int, vector<int>, greater<int>> wait;
    for (size_t i = 1; i <= n; i++)
        star.push({t[i], i});
    ll boil_t = 0;
    while (wait.size() || star.size() || boil.size())
    {
        ll mnt = LLONG_MAX;
        if (boil.size())
            mnt = min(mnt, boil.top().first);
        if (star.size())
            mnt = min(mnt, star.top().first);
        db(mnt);
        // db(wait);
        // db(star);
        // db(boil);
        while (star.size() && star.top().first == mnt)
        {
            db(star.top());
            int x = star.top().second;
            star.pop();
            wait.push(x);
        }
        while (boil.size() && boil.top().first == mnt)
        {
            db(boil.top());
            int x = boil.top().second;
            ans[x] = boil.top().first;
            boil.pop();
            add(x, -1);
        }
        if (wait.size())
        {
            int x = wait.top();
            db(wait.top(), query(x));
            if (!query(x))
            {
                boil_t = max(mnt, boil_t) + p;
                boil.push({boil_t, x});
                add(x, 1);
                wait.pop();
            }
        }
    }
    for (size_t i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    cout << '\n';
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