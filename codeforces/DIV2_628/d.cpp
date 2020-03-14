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

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        ll xoR, sum;
        cin >> xoR >> sum;
        if (xoR == sum && xoR == 0)
        {
            cout << 0 << '\n';
            return;
        }
        if (xoR > sum)
        {
            cout << -1 << '\n';
        }
        else
        {
            vector<ll> v;
            sum -= xoR;
            v.pb(xoR);
            for (size_t i = 0; i < 62; i++)
            {
                if (i == 0)
                {
                    if (sum & 1)
                    {
                        cout << -1 << '\n';
                        return;
                    }
                }
                else
                {
                    if (sum & (1LL << i))
                    {
                        int ok = 0;
                        for (int j = 0; j < v.size(); j++)
                        {
                            if (v[j] & (1LL << (i - 1)))
                            {
                                continue;
                            }
                            ok++;
                            v[j] |= (1LL << (i - 1));
                            if (ok == 2)
                            {
                                break;
                            }
                        }
                        while (ok != 2)
                        {
                            v.pb((1LL << (i - 1)));
                            ++ok;
                        }
                    }
                }
            }
            cout << v.size() << '\n';
            for (auto &x : v)
                cout << x << ' ';
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