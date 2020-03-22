// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#define pc(...)
#endif

#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 1e5 + 5, MOD = 1000000007;

ll ownedMoney[NAX];
class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        for (size_t i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            ownedMoney[u] -= w;
            ownedMoney[v] += w;
        }
        deque<pair<ll, int>> inLoss, inProfit;
        for (size_t i = 1; i <= n; i++)
        {
            if (ownedMoney[i] == 0)
                continue;
            else if (ownedMoney[i] < 0)
                inLoss.pb({-ownedMoney[i], i});
            else
                inProfit.pb({ownedMoney[i], i});
        }
        vector<pair<int, pair<int, ll>>> res;
        sort(all(inProfit));
        sort(all(inLoss));
        reverse(all(inProfit));
        reverse(all(inLoss));

        while (inLoss.size())
        {
            pc(inLoss, inProfit);
            auto lossParty = inLoss.front();
            auto profitParty = inProfit.front();
            auto transaction = min(lossParty.f, profitParty.f);
            res.pb({lossParty.s, {profitParty.s, transaction}});
            inLoss.front().f -= transaction;
            inProfit.front().f -= transaction;
            if (inLoss.front().f == 0)
                inLoss.pop_front();
            if (inProfit.front().f == 0)
                inProfit.pop_front();
        }
        cout << res.size() << '\n';
        for (auto &elem : res)
            cout << elem.f << ' ' << elem.s.f << ' ' << elem.s.s << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}