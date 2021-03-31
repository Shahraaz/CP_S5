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
    vector<int> q(n);
    for (auto &x : q)
    {
        cin >> x;
        --x;
    }
    vector<int> lexmin(n), lexmax(n);
    set<int> mini1, maxi1, to_no_use;
    set<int> mini2, maxi2;
    for (size_t i = 0; i < n; i++)
        to_no_use.insert(q[i]);
    for (size_t i = 0; i < n; i++)
    {
        if (to_no_use.find(i) == to_no_use.end())
        {
            mini1.insert(i);
            mini2.insert(i);
        }
    }
    for (size_t i = 0; i < n; i++)
    {
        int now = q[i];
        if (to_no_use.find(now) != to_no_use.end())
        {
            to_no_use.erase(now);
            lexmax[i] = lexmin[i] = now;

            while (mini1.size())
            {
                auto it = mini1.begin();
                if (*it < now)
                {
                    maxi1.insert(*it);
                    mini1.erase(it);
                }
                else
                    break;
            }

            while (mini2.size())
            {
                auto it = mini2.begin();
                if (*it < now)
                {
                    maxi2.insert(*it);
                    mini2.erase(it);
                }
                else
                    break;
            }
        }
        else
        {
            assert(maxi1.size() && maxi2.size());
            {
                auto it = maxi1.begin();
                lexmin[i] = *it;
                maxi1.erase(it);
            }
            {
                auto it = --maxi2.end();
                lexmax[i] = *it;
                maxi2.erase(it);
            }
        }
    }
    for (auto &x : lexmin)
        cout << x + 1 << ' ';
    cout << '\n';
    for (auto &x : lexmax)
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
        solveCase();
    return 0;
}