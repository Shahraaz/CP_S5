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
        int n1, n2, n3;
        cin >> n1 >> n2 >> n3;
        deque<int> poses[3];
        vector<pair<int, int>> abcd;
        for (size_t i = 0; i < n1; i++)
        {
            int x;
            cin >> x;
            abcd.pb({x, 0});
            poses[0].pb(x);
        }
        for (size_t i = 0; i < n2; i++)
        {
            int x;
            cin >> x;
            abcd.pb({x, 1});
            poses[1].pb(x);
        }
        for (size_t i = 0; i < n3; i++)
        {
            int x;
            cin >> x;
            abcd.pb({x, 2});
            poses[2].pb(x);
        }
        sort(all(poses[0]));
        sort(all(poses[1]));
        sort(all(poses[2]));
        sort(all(abcd));
        ll res = LLONG_MAX;
        for (size_t i = 0; i < abcd.size(); i++)
        {
            int curr = abcd[i].s;
            int next = 0;
            if (curr == 0)
                next = 1;
            else
                next = 0;
            int nnext = 3 - curr - next;
            db(curr, next, nnext);
            if (poses[nnext].size() && poses[next].size())
            {
                ll a = poses[curr].front();
                ll b = poses[next].front();
                ll c = poses[nnext].front();
                res = min(res, (a - b) * (a - b) + (c - b) * (c - b) + (a - c) * (a - c));
                if (b >= c)
                {
                    int diff = (b - a) / 2 + a;
                    auto it = upper_bound(all(poses[nnext]), diff);
                    if (it != poses[nnext].end())
                    {
                        res = min(res, (a - b) * (a - b) + (*it - b) * (*it - b) + (a - *it) * (a - *it));
                    }
                    if (it != poses[nnext].begin())
                    {
                        --it;
                        res = min(res, (a - b) * (a - b) + (*it - b) * (*it - b) + (a - *it) * (a - *it));
                    }
                }
                if (c >= b)
                {
                    swap(c, b);
                    swap(next, nnext);
                    int diff = (b - a) / 2 + a;
                    auto it = upper_bound(all(poses[nnext]), diff);
                    if (it != poses[nnext].end())
                    {
                        res = min(res, (a - b) * (a - b) + (*it - b) * (*it - b) + (a - *it) * (a - *it));
                    }
                    if (it != poses[nnext].begin())
                    {
                        --it;
                        res = min(res, (a - b) * (a - b) + (*it - b) * (*it - b) + (a - *it) * (a - *it));
                    }
                }
                db(a, b, c);
            }
            poses[curr].pop_front();
        }
        cout << res << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
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
