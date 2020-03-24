// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define MULTI_TEST
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
        set<int> s;
        cin >> n;
        for (size_t i = 0; i < n; i++)
        {
            s.insert(i + 1);
        }
        bool ok = true;
        vector<vector<int>> choices;
        vector<bool> okv;
        for (size_t i = 0; i < n; i++)
        {
            int k;
            cin >> k;
            vector<int> pr(k);
            for (auto &x : pr)
                cin >> x;
            choices.pb(pr);
            bool ok1 = false;
            for (auto &x : pr)
            {
                if (s.count(x))
                {
                    s.erase(x);
                    ok1 = true;
                    break;
                }
            }
            okv.pb(ok1);
            if (!ok1)
                ok = false;
        }
        if (ok)
            cout << "OPTIMAL" << '\n';
        else
        {
            cout << "IMPROVE\n";
            for (size_t i = 0; i < n; i++)
            {
                if (okv[i])
                    continue;
                cout << i + 1 << ' ' << *s.begin() << '\n';
                s.erase(s.begin());
                break;
            }
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