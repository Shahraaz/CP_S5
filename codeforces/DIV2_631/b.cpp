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
        vector<int> a(n);
        set<int> left, right;
        map<int, int> L, R;
        for (size_t i = 0; i < n; i++)
        {
            cin >> a[i];
            R[a[i]]++;
            right.insert(a[i]);
        }
        vector<int> resw;
        for (size_t i = 0; (i + 1) < n; i++)
        {
            R[a[i]]--;
            if (R[a[i]] == 0)
                right.erase(a[i]);
            L[a[i]]++;
            left.insert(a[i]);
            int lenl = i + 1;
            int rlen2 = n - lenl;
            if (lenl == left.size() && rlen2 == right.size())
            {
                if (*left.begin() == 1 && *right.begin() == 1)
                    if (*(--left.end()) == lenl && *(--right.end()) == rlen2)
                    {
                        resw.pb(lenl);
                    }
            }
        }
        cout << resw.size() << '\n';
        for (auto &x : resw)
            cout << x << ' ' << n - x << '\n';
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