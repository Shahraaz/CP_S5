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

struct Solution
{
    Solution() {}
    void solveCase()
    {
        int a, b, c;
        cin >> a >> b >> c;
        int m;
        cin >> m;
        map<string, int> mp;
        vector<int> cost[2];
        mp["USB"] = 0;
        mp["PS/2"] = 1;
        for (size_t i = 0; i < m; i++)
        {
            int c;
            cin >> c;
            string Rype;
            cin >> Rype;
            cost[mp[Rype]].pb(c);
        }
        ll computerEquipped, totalCost;
        computerEquipped = totalCost = 0;
        sort(all(cost[0]));
        sort(all(cost[1]));
        reverse(all(cost[0]));
        reverse(all(cost[1]));
        while (a > 0 && cost[0].size())
        {
            a--;
            computerEquipped++;
            totalCost += cost[0].back();
            cost[0].pop_back();
        }
        while (b > 0 && cost[1].size())
        {
            b--;
            computerEquipped++;
            totalCost += cost[1].back();
            cost[1].pop_back();
        }
        while (cost[1].size())
        {
            cost[0].pb(cost[1].back());
            cost[1].pop_back();
        }
        sort(all(cost[0]));
        sort(all(cost[1]));
        reverse(all(cost[0]));
        reverse(all(cost[1]));
        a = c;
        while (a > 0 && cost[0].size())
        {
            a--;
            computerEquipped++;
            totalCost += cost[0].back();
            cost[0].pop_back();
        }
        cout << computerEquipped << ' ' << totalCost << '\n';
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
