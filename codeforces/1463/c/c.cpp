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
    vector<pair<ll, ll>> vecc(n);
    for (size_t i = 0; i < n; i++)
    {
        ll t, x;
        cin >> t >> x;
        vecc[i] = {t, x};
    }
    ll robot = 0, prev = 0;
    int cnt = 0;
    ll nextactiveTime = 0;
    ll prevTime = 0;
    for (size_t i = 0; i < n; i++)
    {
        ll t = vecc[i].first, x = vecc[i].second;
        db(i, t, x, nextactiveTime, robot, prev, prevTime, nextactiveTime);
        if (nextactiveTime <= t)
        {
            db("a");
            ll nnext = (i + 1) == n ? (1e15) : vecc[i + 1].first;
            prevTime = t;
            nextactiveTime = t + abs(robot - x);
            db(nnext);
            if (nextactiveTime <= nnext)
            {
                db("i", "a");
                cnt++;
            }
            prev = robot;
            robot = x;
        }
        else
        {
            db("b");
            ll nnext = (i + 1) == n ? (1e15) : vecc[i + 1].first;
            db(nnext);
            if (prev <= robot)
            {
                if (prev <= x && x <= robot)
                {
                    ll timetoreach = abs(prev - x) + prevTime;
                    db("c", timetoreach);
                    if (t <= timetoreach && timetoreach <= nnext)
                    {
                        db("i", "b");
                        cnt++;
                    }
                }
            }
            else
            {
                if (prev >= x && x >= robot)
                {
                    ll timetoreach = abs(prev - x) + prevTime;
                    db("d", timetoreach);
                    if (t <= timetoreach && timetoreach <= nnext)
                    {
                        db("i", "c");
                        cnt++;
                    }
                }
            }
        }
    }
    cout << cnt << '\n';
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