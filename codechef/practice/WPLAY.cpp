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

const int NAX = 2e5 + 5, MOD = 1000000007;

int pos[1 << 16];
int dp[1 << 16];

class Solution
{
    unordered_set<string> uset;
    int r, c, k;
    vector<string> g;
    inline int go(int ac)
    {
        int &ret = dp[ac];
        if (ret >= 0)
            return ret;
        int op = 0, ones[22];
        for (int i = 0; i < k; i++)
            if ((ac & (1 << i)) > 0)
                ones[op++] = i;
        ret = 0;
        for (int i = 1; i < (1 << op); i++)
        {
            int mask = 0;
            for (int j = 0; j < op; j++)
                if (i & (1 << j))
                    mask |= (1 << ones[j]);
            // printf("%d %d\n", ac, mask);

            if (pos[mask])
            {
                int next = go(ac ^ mask);
                if (next == 0)
                {
                    // cout << ac << ' ' << 1 << '\n';
                    return ret = 1;
                }
            }
        }
        // cout << ac << ' ' << 0 << '\n';
        return ret = 0;
    }

private:
public:
    Solution()
    {
        int d;
        cin >> d;
        for (int i = 0; i < d; i++)
        {
            string str;
            cin >> str;
            sort(all(str));
            uset.insert(str);
        }
        cin >> r >> c;
        g.resize(r);
        k = r * c;
    }
    ~Solution() {}
    void solveCase()
    {
        int t;
        cin >> t;
        while (t--)
        {
            for (int i = 0; i < r; i++)
                cin >> g[i];
            for (int i = 0; i < (1 << k); i++)
            {
                string tmep = "";
                for (int j = 0; j < k; j++)
                    if (i & (1 << j))
                    {
                        int x = j % c, y = j / c;
                        tmep += g[y][x];
                    }
                sort(all(tmep));
                pos[i] = uset.find(tmep) != uset.end();
                // cout << i << ' ' << pos[i] << '\n';
            }
            memset(dp, -1, sizeof dp);
            if (go((1 << k) - 1))
                cout << "Alice\n";
            else
                cout << "Bob\n";
        }
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