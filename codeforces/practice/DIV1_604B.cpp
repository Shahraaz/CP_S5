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
        vector<int> cnt(4);
        for (auto &x : cnt)
            cin >> x;
        int n = accumulate(all(cnt), 0);
        for (int i = 0; i < 4; i++)
        {
            auto cnt2 = cnt;
            if (cnt2[i] > 0)
            {
                vector<int> res = {i};
                cnt2[i]--;
                auto check = [&](int x) {
                    return x >= 0 && x < 4 && cnt2[x];
                };
                for (size_t i = 1; i < n; i++)
                {
                    int back = res.back();
                    if (check(back - 1))
                    {
                        cnt2[back - 1]--;
                        res.pb(back - 1);
                    }
                    else if (check(back + 1))
                    {
                        cnt2[back + 1]--;
                        res.pb(back + 1);
                    }
                    else
                        break;
                }
                if (res.size() == n)
                {
                    cout << "YES\n";
                    for (auto &x : res)
                        cout << x << ' ';
                    cout << '\n';
                    return;
                }
            }
        }
        cout << "NO\n";
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