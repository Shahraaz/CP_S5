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
        cin >> str;
        int n = str.length();
        vector<int> len(n, -1);
        for (int i = 0; i < n; i++)
        {
            if (str[i] == '(')
                len[i] = -1;
            else if (str[i] == ')')
            {
                db("found ) at", i);
                if (i > 0)
                {
                    if (str[i - 1] == '(')
                    {
                        len[i] = 2;
                        if (i - 2 >= 0)
                            if (len[i - 2] >= 0)
                                len[i] += len[i - 2];
                    }
                    else
                    {
                        int l = len[i - 1];
                        if (l != -1)
                        {
                            int idx = i - 1 - (l - 1) - 1;
                            db(idx, i);
                            if (idx >= 0)
                            {
                                if (str[idx] == '(')
                                {
                                    len[i] = 2 + l;
                                    if (idx - 1 >= 0)
                                    {
                                        if (len[idx - 1] >= 0)
                                            len[i] += len[idx - 1];
                                    }
                                }
                            }
                        }
                    }
                }
            }
            db(i, len[i]);
        }
        pc(len);
        int maxi = *max_element(all(len));
        if (maxi > 0)
            cout << maxi << ' ' << count(all(len), maxi);
        else
            cout << 0 << ' ' << 1 << '\n';
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