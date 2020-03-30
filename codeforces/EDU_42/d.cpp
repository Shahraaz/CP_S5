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
        int n, x;
        cin >> n;
        map<ll, deque<int>> deq;
        for (size_t i = 0; i < n; i++)
        {
#ifdef LOCAL
            x = 1000000000;
            deq[x].pb(i);
#else
            cin >> x;
            deq[x].pb(i);
#endif
        }
        vector<ll> res(n, -1);
        for (auto &myList : deq)
        {
            ll num = myList.f;
            db(num, myList.s.size());
            sort(all(myList.s));
            while (myList.s.size() >= 2)
            {
                int idx1, idx2;
                idx1 = myList.s.front();
                myList.s.pop_front();
                idx2 = myList.s.front();
                myList.s.pop_front();
                deq[num * 2].pb(idx2);
            }
            if (myList.s.size())
                res[myList.s.front()] = num;
        }
        cout << n - count(all(res), -1) << '\n';
        for (size_t i = 0; i < n; i++)
        {
            if (res[i] >= 0)
                cout << res[i] << ' ';
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