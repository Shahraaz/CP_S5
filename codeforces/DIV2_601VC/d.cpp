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
    char getIdx(int x)
    {
        if (x < 10)
            return '0' + x;
        if (x < 10 + 26)
            return 'a' + x - 10;
        return x - 36 + 'A';
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m, c;
        cin >> n >> m >> c;
        vector<string> mp(n);
        vector<vector<bool>> vis(n, vector<bool>(m));
        int cntRice = 0;
        for (auto &x : mp)
        {
            cin >> x;
            cntRice += count(all(x), 'R');
        }
        int mini = cntRice / c, rem = cntRice % c;
        int ctr = 1;
        int collect = mini + (rem > 0);
        db(n, m, c, mini, rem, cntRice);
        pc(mp);
        if (rem > 0)
            rem--;
        for (size_t i = 0; i < n; i++)
        {
            if (i & 1)
            {
                for (size_t j = 0; j < m; j++)
                {
                    if (ctr == c)
                    {
                        mp[i][j] = getIdx(ctr - 1);
                    }
                    else
                    {
                        if (mp[i][j] == 'R')
                            collect--;
                        mp[i][j] = getIdx(ctr - 1);
                        if (collect == 0)
                        {
                            ctr++;
                            collect = mini + (rem > 0);
                            if (rem > 0)
                                rem--;
                        }
                    }
                }
            }
            else
            {
                for (int j = m - 1; j >= 0; j--)
                {
                    if (ctr == c)
                    {
                        mp[i][j] = getIdx(ctr - 1);
                    }
                    else
                    {
                        if (mp[i][j] == 'R')
                            collect--;
                        mp[i][j] = getIdx(ctr - 1);
                        if (collect == 0)
                        {
                            ctr++;
                            collect = mini + (rem > 0);
                            if (rem > 0)
                                rem--;
                        }
                    }
                }
            }
        }
        for (auto &x : mp)
            cout << x << '\n';
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