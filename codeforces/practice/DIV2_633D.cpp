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

bool been[NAX];
vector<int> vec[NAX];
int vec1[NAX];

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        for (size_t i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            vec[u].pb(v);
            vec[v].pb(u);
        }
        set<int> leafs;
        vector<int> L;
        for (size_t i = 1; i <= n; i++)
        {
            if (vec[i].size() == 1)
            {
                leafs.insert(i);
                L.pb(i);
            }
        }
        int diff = n - 1;
        for (size_t i = 1; i <= n; i++)
        {
            int l = 0;
            for (auto &u : vec[i])
            {
                if (leafs.count(u))
                    l++;
            }
            if (l > 0)
                diff -= l - 1;
        }
        int small = 1;
        function<void(int, int)> dfs = [&](int s, int p) -> void {
            if (been[s])
                return;
            been[s] = true;
            vec1[s] = 1 - vec1[p];
            for (auto child : vec[s])
                dfs(child, s);
        };
        dfs(1, 0);
        int good = vec1[L.front()];
        for (auto &child : L)
            if (vec1[child] != good)
                small = 3;
        cout << small << ' ' << diff << '\n';
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
