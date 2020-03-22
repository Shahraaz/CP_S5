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
        int n;
        cin >> n;
        n = 2 * n;
        vector<vector<int>> cnt(101);
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            cnt[x].pb(i);
        }
        vector<int> clr(n);
        vector<pair<int, int>> p;
        int clred = 0;
        set<int> f, s;
        for (size_t i = 0; i < 101; i++)
        {
            if (cnt[i].size() == 1)
            {
                if (clred & 1)
                {
                    f.insert(i);
                    clr[cnt[i].back()] = 1;
                }
                else
                {
                    s.insert(i);
                    clr[cnt[i].back()] = 2;
                }
                cnt[i].pop_back();
                clred++;
            }
            else if (cnt[i].size() > 1)
            {
                p.pb({i, cnt[i].back()});
                cnt[i].pop_back();

                p.pb({i, cnt[i].back()});
                cnt[i].pop_back();
            }
        }
        for (auto &elem : p)
        {
            db(elem);
            if (clred & 1)
            {
                f.insert(elem.f);
                clr[elem.s] = 1;
            }
            else
            {
                s.insert(elem.f);
                clr[elem.s] = 2;
            }
            clred++;
        }
        for (size_t i = 0; i < 101; i++)
        {
            while (cnt[i].size() > 0)
            {
                if (clred & 1)
                {
                    f.insert(i);
                    clr[cnt[i].back()] = 1;
                }
                else
                {
                    s.insert(i);
                    clr[cnt[i].back()] = 2;
                }
                cnt[i].pop_back();
                clred++;
            }
        }
        pc(first, second);
        db(first.size(), second.size());
        cout << ll(first.size()) * second.size() << '\n';
        for (auto &x : clr)
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