
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

const int NAX = 2e5 + 5, MOD = 1000000009;

int n;
int x[NAX], y[NAX];
map<pair<int, int>, int> mp;
int r[NAX];
set<int> s;
int ans[NAX];
int vis[NAX];

class Solution
{
private:
    int ok(int i)
    {
        int nx, ny, te;
        nx = x[i] - 1;
        ny = y[i] + 1;
        te = mp[{nx, ny}];
        if (te != 0 && r[te - 1] == 1)
            return false;
        nx = x[i];
        te = mp[{nx, ny}];
        if (te != 0 && r[te - 1] == 1)
            return false;
        nx = x[i] + 1;
        ny = y[i] + 1;
        te = mp[{nx, ny}];
        if (te != 0 && r[te - 1] == 1)
            return false;
        return true;
    }
    void changeerase(int i)
    {
        int nx, ny, te;
        nx = x[i] - 1, ny = y[i] - 1;
        te = mp[{nx, ny}];
        if (te)
            if (vis[te - 1] == -1)
            {
                vis[te - 1] = 0;
                s.erase(te - 1);
                return;
            }
        nx = x[i], ny = y[i] - 1;
        te = mp[{nx, ny}];
        if (te)
            if (vis[te - 1] == -1)
            {
                vis[te - 1] = 0;
                s.erase(te - 1);
                return;
            }
        nx = x[i] + 1, ny = y[i] - 1;
        te = mp[{nx, ny}];
        if (te)
            if (vis[te - 1] == -1)
            {
                vis[te - 1] = 0;
                s.erase(te - 1);
                return;
            }
    }
    void changeadd(int i)
    {
        int nx, ny, te;
        nx = x[i] - 1, ny = y[i] - 1;
        te = mp[{nx, ny}];
        if (te)
            if (ok(te - 1))
            {
                vis[te - 1] = -1;
                s.insert(te - 1);
            }
        nx = x[i], ny = y[i] - 1;
        te = mp[{nx, ny}];
        if (te)
            if (ok(te - 1))
            {
                vis[te - 1] = -1;
                s.insert(te - 1);
            }
        nx = x[i] + 1, ny = y[i] - 1;
        te = mp[{nx, ny}];
        if (te)
            if (ok(te - 1))
            {
                vis[te - 1] = -1;
                s.insert(te - 1);
            }
    }
    void update(int i)
    {
        int nx, ny, te;
        nx = x[i] - 1;
        ny = y[i] + 1;
        te = mp[{nx, ny}];
        if (te != 0)
        {
            r[te - 1]--;
            if (r[te - 1] == 1)
                changeerase(te - 1);
        }
        nx = x[i];
        te = mp[{nx, ny}];
        if (te != 0)
        {
            r[te - 1]--;
            if (r[te - 1] == 1)
                changeerase(te - 1);
        }
        nx = x[i] + 1;
        te = mp[{nx, ny}];
        if (te != 0)
        {
            r[te - 1]--;
            if (r[te - 1] == 1)
                changeerase(te - 1);
        }
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n;
        for (size_t i = 0; i < n; i++)
        {
            cin >> x[i] >> y[i];
            mp[{x[i], y[i]}] = i + 1;
        }
        for (size_t i = 0; i < n; i++)
        {
            int nx = x[i] - 1, ny = y[i] - 1;
            if (mp[{nx, ny}] != 0)
                r[i]++;
            nx++;
            if (mp[{nx, ny}] != 0)
                r[i]++;
            nx++;
            if (mp[{nx, ny}] != 0)
                r[i]++;
        }
        for (size_t i = 0; i < n; i++)
            if (ok(i))
            {
                s.insert(i);
                vis[i] = -1;
            }

        for (size_t i = 0; i < n; i++)
        {
            db(s);
            auto it = s.begin();
            if (i % 2 == 0)
                it = --s.end();
            ans[i] = *it;
            int index = *it;
            s.erase(index);
            mp[{x[index], y[index]}] = 0;
            vis[index] = 1;
            update(index);
            changeadd(index);
        }
        ll aa = 0;
        for (size_t i = 0; i < n; i++)
        {
#ifdef LOCAL
            cout << ans[i] << ' ';
#else

#endif
            aa = (aa * n) % MOD;
            aa = (aa + ans[i]) % MOD;
        }
        cout << '\n';
        cout << aa << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
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