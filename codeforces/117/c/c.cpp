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
    vector<string> grid(n);
    for (auto &x : grid)
        cin >> x;
    db(n);
    db(grid);
    vector<int> vis(n), cycle;
    vector<int> st;
    function<bool(int, int)> dfs = [&](int node, int par) -> bool {
        vis[node] = 1;
        st.pb(node);
        db(node, par, vis[node], st);
        for (size_t i = 0; i < n; i++)
        {
            if (grid[node][i] == '0')
                continue;
            if (vis[i] == 0)
            {
                if (dfs(i, node))
                    return true;
            }
            else if (vis[i] == 1)
            {
                //cycle found
                // i -> a -> b .. . . . .. -> node
                db(i);
                while (st.size())
                {
                    db(st.back());
                    cycle.pb(st.back());
                    if (st.back() == i)
                        break;
                    st.pop_back();
                }

                return true;
            }
        }
        st.pop_back();
        vis[node] = 2;
        return false;
    };
    for (size_t i = 0; i < n; i++)
    {
        if (!dfs(i, i))
            continue;
        reverse(all(cycle));
        while (true)
        {
            db(cycle);
            assert(cycle.size() >= 3);
            int sz = cycle.size();
            int a0 = cycle[sz - 3];
            int a1 = cycle[sz - 2];
            int a2 = cycle[sz - 1];
            if (grid[a2][a0] == '1')
            {
                cout << a0 + 1 << ' ';
                cout << a1 + 1 << ' ';
                cout << a2 + 1 << '\n';
                return;
            }
            cycle.pop_back();
            cycle.pop_back();
            cycle.pb(a2);
        }
        assert(false);
    }
    cout << -1 << '\n';
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