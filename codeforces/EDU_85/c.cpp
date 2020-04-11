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
        cin >> n;
        vector<pair<ll, ll>> a(n);
        for (auto &x : a)
            cin >> x.f >> x.s;
        vector<bool> canGetKilled(n);
        int cnt = 0;
        for (size_t i = 0; i < n; i++)
        {
            int x = (i - 1 + n) % n;
            if (a[x].s >= a[i].f)
            {
                canGetKilled[i] = true;
                cnt++;
            }
        }
        pc(canGetKilled);
        pc(a);
        if (cnt == n)
        {
            ll res = LLONG_MAX;
            for (size_t i = 0; i < n; i++)
                res = min(res, a[i].f);
            cout << res << '\n';
        }
        else
        {
            ll res = 0, aux = LLONG_MAX;
            vector<ll> discount(n);
            for (size_t i = 0; i < n; i++)
            {
                int x = (i - 1 + n) % n;
                discount[i] = max(0LL, a[i].f - a[x].s);
                res += discount[i];
            }
            for (size_t i = 0; i < n; i++)
                aux = min(aux, res - discount[i] + a[i].f);
            db(res, aux);
            cout << aux << '\n';
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