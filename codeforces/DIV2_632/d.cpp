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
        string str;
        int n, k;
        cin >> n >> k;
        cin >> str;
        deque<deque<int>> ppos;
        auto correct = [&str]() -> deque<int> {
            deque<int> poses;
            for (size_t i = 0; (i + 1) < str.size(); i++)
            {
                if (str[i] == 'R' && str[i + 1] == 'L')
                {
                    swap(str[i], str[i + 1]);
                    ++i;
                    poses.pb(i);
                }
            }
            return poses;
        };
        int totalMoves = 0;
        // vector<int> vv;
        auto kback = k;
        while (true)
        {
            auto state = correct();
            db(str);
            pc(state);
            totalMoves += state.size();
            if (state.size() == 0)
                break;
            ppos.pb(state);
            // for (auto &x : state)
            //     vv.pb(x);
        }
        vector<vector<int>> res;
        db(totalMoves, ppos.size(), k);
        if (totalMoves < k || ppos.size() > k)
        {
            cout << -1 << '\n';
            return;
        }
        else
        {
            // int fptr = 0, sptr = 0;
            while (k > ppos.size())
            {
                if (ppos.front().size())
                {
                    res.pb({ppos.front().front()});
                    ppos.front().pop_front();
                    --k;
                }
                if (ppos.front().size() == 0)
                    ppos.pop_front();
            }
            while (ppos.size() && ppos.front().size() == 0)
                ppos.pop_front();
        }
        if (res.size() + ppos.size() != kback)
        {
            cout << -1 << '\n';
            return;
        }
        for (auto &x : res)
        {
            if (x.size() == 0)
                continue;
            cout << x.size() << ' ';
            for (auto &y : x)
            {
                cout << y << ' ';
            }
            cout << '\n';
        }
        for (auto &x : ppos)
        {
            if (x.size() == 0)
                continue;
            cout << x.size() << ' ';
            for (auto &y : x)
            {
                cout << y << ' ';
            }
            cout << '\n';
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