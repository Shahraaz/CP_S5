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
        if (n == 1)
        {
            cout << 1 << ' ' << 1 << '\n';
            return;
        }
        if (n == 2)
        {
            cout << "1 1 2 2\n";
            return;
        }
        vector<int> v(2 * (1e6) + 1, -1);
        int pre = 1;
        for (size_t i = 1; i <= n; i += 2)
        {
            v[pre] = i;
            v[pre + n - i] = i;
            pre++;
        }
        pre = n + 1;
        for (size_t i = 2; i <= n; i += 2)
        {
            v[pre] = i;
            v[pre + n - i] = i;
            ++pre;
        }
        for (size_t i = 1; i <= 2 * n; i++)
            if (v[i] == -1)
                cout << n << ' ';
            else
                cout << v[i] << ' ';
        cout << '\n';
#ifdef LOCAL
        for (size_t i = 1; i <= n; i++)
        {
            cout << i << ' ';
            vector<int> pos;
            for (size_t j = 1; j <= 2 * n; j++)
            {
                if (v[j] == i)
                    pos.pb(j);
                // cout << j << ' ';
            }
            pc(pos);
        }

#else

#endif
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