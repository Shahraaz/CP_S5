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

void go(pair<int, int> &now, char c)
{
    if (c == 'U')
        now.first++;
    if (c == 'D')
        now.first--;
    if (c == 'L')
        now.second--;
    if (c == 'R')
        now.second++;
}

void solveCase()
{
    string str;
    cin >> str;
    pair<int, int> curr;
    map<char, vector<pair<int, int>>> mp;
    map<pair<int, int>, int> ctr;
    for (auto &x : str)
    {
        go(curr, x);
        ctr[curr]++;
        mp[x].pb(curr);
    }
    db(mp);
    db(ctr);
    db(curr);
    for (auto &x : ctr)
    {
        pair<int, int> curr;
        for (auto &y : str)
        {
            auto next = curr;
            go(next, y);
            if (next != x.first)
                curr = next;
        }
        if (curr.first == 0 && curr.second == 0)
        {
            cout << x.first.second << ' ' << x.first.first << '\n';
            return;
        }
    }
    cout << 0 << ' ' 0 << '\n';
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