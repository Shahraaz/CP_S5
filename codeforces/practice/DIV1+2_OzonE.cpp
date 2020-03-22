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
        int n, m;
        cin >> n >> m;
        vector<int> ans(n);
        vector<int> sumCnt(2 * n + 1);
        int remain = m;
        int j;
        for (j = 0; j < n; j++)
        {
            if (remain <= sumCnt[j + 1])
                break;
            remain -= sumCnt[j + 1];
            ans[j] = j + 1;
            for (size_t i = 0; i < j; i++)
                ++sumCnt[ans[i] + ans[j]];
            db(j);
            pc(sumCnt);
        }
        if (j == n)
        {
            cout << -1;
            return;
        }
        int x = j + 1;
        while (remain != sumCnt[x])
        {
            ++x;
            db(x, remain);
            pc(sumCnt);
        }
        ans[j] = x;
        int maxSum = (j == 0) ? ans[j] : (ans[j - 1] + ans[j]);
        int curr = maxSum + 1;
        for (int i = j + 1; i < n; i++)
        {
            ans[i] = curr;
            curr += 2 * (maxSum + 1);
        }
        for (auto &x : ans)
            cout << x << ' ';
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