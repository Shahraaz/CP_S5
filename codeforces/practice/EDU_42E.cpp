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
        deque<ll> nodeList[3];
        int n;
        cin >> n;
        for (size_t i = 0; i < n; i++)
        {
            char c;
            int x;
            cin >> x >> c;
            switch (c)
            {
            case 'R':
                nodeList[0].pb(x);
                break;
            case 'P':
                nodeList[2].pb(x);
                break;
            case 'B':
                nodeList[1].pb(x);
                break;

            default:
                break;
            }
        }
        auto solve = [&](deque<ll> &purple, deque<ll> &red) -> ll {
            if (red.size() == 0)
                exit(2);
            int fptr = 0, nextptr = 1, sndPtr = 0;
            ll ret = 0;
            pc(purple, red);
            while (nextptr < purple.size())
            {
                ll minMiddle = MOD;
                ll maxMiddle = -MOD;
                while (sndPtr < red.size() && red[sndPtr] < purple[nextptr])
                {
                    minMiddle = min(minMiddle, 0LL + red[sndPtr]);
                    maxMiddle = max(maxMiddle, 0LL + red[sndPtr]);
                    ++sndPtr;
                }
                if (minMiddle != MOD)
                    ret += min(abs(maxMiddle - purple[fptr]), abs(purple[nextptr] - minMiddle));
                ++fptr, ++nextptr;
            }
            return ret;
        };
        ll res = 0;
        if (nodeList[2].size() == 0)
        {
            if (nodeList[0].size())
                res += nodeList[0].back() - nodeList[0].front();
            if (nodeList[1].size())
                res += nodeList[1].back() - nodeList[1].front();
        }
        else
        {
            if (nodeList[2].size() != n)
            {
                if (nodeList[0].size() == 0)
                {
                    res = max(nodeList[2].back(), nodeList[1].back()) - min(nodeList[2].front(), nodeList[1].front());
                }
                else if (nodeList[1].size() == 0)
                {
                    res = max(nodeList[2].back(), nodeList[0].back()) - min(nodeList[2].front(), nodeList[0].front());
                }
                else
                {
                    nodeList[2].push_front(-10LL * MOD);
                    nodeList[2].push_back(10LL * MOD);
                    res = nodeList[2].back() - nodeList[2].front();
                    res += solve(nodeList[2], nodeList[1]);
                    res += solve(nodeList[2], nodeList[0]);
                }
            }
            else
                res = nodeList[2].back() - nodeList[2].front();
        }
        cout << res << '\n';
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