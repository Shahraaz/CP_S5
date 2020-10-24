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

int x[NAX], y[NAX], s[NAX], w[NAX], mark[NAX], colmark[NAX];

vector<int> v[NAX], a;

void solveCase()
{
    int n, m;
    cin >> n >> m;
    for (size_t i = 0; i < n; i++)
        cin >> w[i + 1];
    for (size_t i = 0; i < m; i++)
    {
        cin >> x[i] >> y[i];
        s[x[i]]++;
        s[y[i]]++;
        v[x[i]].pb(i);
        v[y[i]].pb(i);
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
    for (size_t i = 1; i <= n; i++)
    {
        if (s[i])
            Q.push({max(0, s[i] - w[i]), i});
        else
            colmark[i] = 1;
    }

    while (Q.size())
    {
        auto top = Q.top();
        Q.pop();
        if (top.f != max(0, s[top.s] - w[top.s]))
            continue;
        if (top.f > 0)
        {
            cout << "DEAD\n";
            return;
        }
        int id = top.s;
        set<int> wt;
        for (auto &u : v[id])
        {
            if (mark[u])
                continue;
            a.pb(u);
            mark[u] = 1;
            if (x[u] == id)
                swap(x[u], y[u]);
            if (!colmark[x[u]])
                wt.insert(x[u]);
            s[x[u]]--;
        }
        for (auto &u : wt)
        {
            if (s[u])
            {
                if (max(0, s[u] - w[u]) == 0)
                    colmark[u] = 1;
                Q.push({max(0, s[u] - w[u]), u});
            }
        }
    }
    cout << "ALIVE\n";
    reverse(all(a));
    for (auto x : a)
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
    // cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
