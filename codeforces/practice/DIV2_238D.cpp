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

const int NAX = 1e6 + 5, MOD = 1000000007;

bool vis[NAX];

class Solution
{
private:
    int n;
    int getSym(int x)
    {
        return 1e6 + 1 - x;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n;
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            vis[x] = true;
        }
        int cat = 0;
        vector<int> res;
        for (size_t i = 1; 2 * i <= 1e6; i++)
        {
            if (vis[i])
            {
                if (!vis[getSym(i)])
                {
                    res.pb(getSym(i));
                    vis[getSym(i)] = true;
                }
                else
                    ++cat;
            }
            else
            {
                if (vis[getSym(i)])
                {
                    res.pb(i);
                    vis[i] = true;
                }
            }
        }
        for (size_t i = 1; (2 * i <= 1e6) && cat; i++)
        {
            if (cat && !vis[i])
            {
                cat--;
                res.pb(getSym(i));
                vis[getSym(i)] = true;
                res.pb(i);
                vis[i] = true;
            }
        }
        cout << res.size() << '\n';
        for (auto &x : res)
            cout << x << ' ';
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