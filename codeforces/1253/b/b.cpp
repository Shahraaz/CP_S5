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
const int NAX = 1e6 + 5, MOD = 1000000007;

vector<int> pos_poses[NAX];
// vector<int> neg_poses[NAX];

void no()
{
    cout << "-1\n";
    exit(0);
}

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        a[i] = x;
        db(i, x);
        if (x > 0)
        {
            if (pos_poses[x].size() && pos_poses[x].back() > 0)
                no();
            pos_poses[x].pb(i);
        }
        else
        {
            if (pos_poses[-x].empty() || pos_poses[-x].back() < 0)
                no();
            pos_poses[-x].pb(-i);
        }
    }
    for (size_t i = 0; i < NAX; i++)
        if (pos_poses[i].size() & 1)
            no();
    vector<int> res;
    db(a);
    for (int i = n; i >= 1;)
    {
        if (a[i] > 0)
            no();
        int j = i;
        int toreach = j;
        int maxleft = -1;
        db(i);
        while (toreach <= j)
        {
            db(j, a[j], toreach, maxleft, pos_poses[abs(a[j])]);
            if (a[j] < 0)
            {
                pos_poses[-a[j]].pop_back();
                toreach = min(toreach, abs(pos_poses[-a[j]].back()));
                pos_poses[-a[j]].pop_back();
                if (pos_poses[-a[j]].size())
                    maxleft = max(maxleft, abs(pos_poses[-a[j]].back()));
            }
            db(j, toreach, maxleft, pos_poses[abs(a[j])]);
            if (j <= maxleft)
                no();
            --j;
        }
        res.pb(i - j);
        i = j;
    }
    reverse(all(res));
    cout << res.size() << '\n';
    for (auto &c : res)
        cout << c << ' ';
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