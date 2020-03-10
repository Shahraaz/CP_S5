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

const int NAX = 3e2 + 5, MOD = 1000000007;

int dp[NAX][NAX];
class Solution
{
private:
    string str;
    set<string> dict;
    int grundy(int start, int end)
    {
        if (start > end)
            return 0;
        int &ret = dp[start][end];
        if (ret >= 0)
            return ret;
        set<int> reach;
        for (int pos = start; pos <= end; pos++)
            for (int rear = pos; rear <= end; ++rear)
                if (dict.count(str.substr(pos, rear - pos + 1)))
                    reach.insert(grundy(start, pos - 1) ^ grundy(rear + 1, end));
        ret = 0;
        while (reach.count(ret))
            ++ret;
        db(start, end, ret);
        return ret;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> str;
        int n;
        cin >> n;
        dict.clear();
        for (int i = 0; i < n; i++)
        {
            string str;
            cin >> str;
            dict.insert(str);
        }
        memset(dp, -1, sizeof dp);
        cout << (grundy(0, str.length() - 1) == 0 ? "Tracy" : "Teddy") << '\n';
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