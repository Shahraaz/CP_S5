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

const int NAX = 1e6 + 5, MOD = 1000000007;

vector<int> adj[NAX];
vector<int> cycle_indices[NAX];
vector<int> cycle_elements[NAX];
int cycle_head[NAX], res[NAX];

struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        memset(cycle_head, -1, sizeof cycle_head);
        for (size_t i = 1; i <= n; i++)
        {
            int x;
            cin >> x;
            adj[i].pb(x);
        }
        for (size_t i = 1; i <= n; i++)
        {
            if (cycle_head[i] >= 0)
                continue;
            queue<int> Q;
            Q.push(i);
            while (Q.size())
            {
                auto top = Q.front();
                cycle_head[top] = i;
                cycle_elements[i].pb(top);
                Q.pop();
                int next = adj[top][0];
                if (cycle_head[next] == -1)
                    Q.push(next);
            }
            cycle_indices[cycle_elements[i].size()].pb(i);
            db(i, cycle_elements[i]);
        }
        for (size_t i = 1; i <= n; i++)
        {
            if (i & 1)
            {
                for (auto &idx : cycle_indices[i])
                {
                    int rptr = i / 2 + 1, lptr = 0;
                    lptr %= i;
                    rptr %= i;
                    bool b = false;
                    for (size_t j = 0; j < i; j++)
                    {
                        db(lptr, rptr);
                        res[cycle_elements[idx][lptr]] = cycle_elements[idx][rptr];
                        // if (b)
                        //     rptr++;
                        // else
                        lptr++;
                        // lptr++, rptr++;
                        lptr %= i;
                        rptr %= i;
                        swap(lptr, rptr);
                        // b = !b;
                    }
                }
            }
            else
            {
                if (cycle_indices[i].size() & 1)
                {
                    cout << "-1\n";
                    return;
                }
                for (size_t j = 0; j < cycle_indices[i].size(); j += 2)
                {
                    int h1 = cycle_indices[i][j];
                    int h2 = cycle_indices[i][j + 1];
                    for (size_t k = 0; k < i; k++)
                    {
                        int a = cycle_elements[h1][k];
                        int b = cycle_elements[h2][k];
                        res[a] = b;
                        res[b] = cycle_elements[h1][(k + 1) % i];
                    }
                }
            }
        }
        for (size_t i = 1; i <= n; i++)
            cout << res[i] << ' ';
        cout << '\n';
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
