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
    set<pair<int, int>> ss;
    const int INF = MOD, NEG_INF = -MOD;
    int n, prev = 0;
    cin >> n;
    vector<int> b(n);
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        b[i] = x;
    }
    int ptr = 0;
    for (size_t i = 0; i < n; i++)
    {
        int x = b[i];
        db(i, x, ss);
        // cin >> x;
        if (i == 0)
        {
            ss.insert({x, ++ptr});
            prev = x;
            continue;
        }
        if (prev == x)
        {
            ss.insert({INF, ++ptr});
            ss.insert({NEG_INF, ++ptr});
        }
        else if (prev < x)
        {
            auto it = ss.lower_bound({prev, MOD});
            assert(it != ss.begin());
            --it;
            if (next(it) == ss.end())
            {
                ss.insert({INF, ++ptr});
                ss.insert({x, ++ptr});
            }
            else
            {
                ++it;
                if (it->first < x)
                {
                    cout << "NO\n";
                    return;
                }
                else if (it->first == x)
                {
                    ss.insert({INF, ++ptr});
                    ss.insert({INF, ++ptr});
                }
                else
                {
                    ss.insert({x, ++ptr});
                    ss.insert({INF, ++ptr});
                }
            }
        }
        else
        {
            auto it = ss.lower_bound({prev, MOD});
            assert(it != ss.begin());
            --it;
            if ((it) == ss.begin())
            {
                ss.insert({NEG_INF, ++ptr});
                ss.insert({x, ++ptr});
            }
            else
            {
                --it;
                if (x < it->first)
                {
                    cout << "NO\n";
                    return;
                }
                else if (it->first == x)
                {
                    ss.insert({NEG_INF, ++ptr});
                    ss.insert({NEG_INF, ++ptr});
                }
                else
                {
                    ss.insert({x, ++ptr});
                    ss.insert({NEG_INF, ++ptr});
                }
            }
        }
        prev = x;
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
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}