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
int dx[] = {0, 1};
int dy[] = {1, 0};

class Solution
{
private:
    int n, m, found;
    vector<string> s;
    bool isValid(int i, int j)
    {
        return 0 <= i && i < n && 0 <= j && j < m;
    }
    int dfs(int i, int j)
    {
        if (i == n - 1 && j == m - 1)
            return found = 1;
        if (found)
            return found;
        db(i, j);
        s[i][j] = '#';
        int res = 0;
        for (size_t k = 0; k < 2; k++)
        {
            int x1 = i + dx[k];
            int y1 = j + dy[k];
            // db(x1, y1);
            if (isValid(x1, y1) && s[x1][y1] == '.')
                res |= dfs(x1, y1);
            // db(res);
            if (found)
                return found;
        }
        return res;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n >> m;
        s.resize(n);
        for (auto &row : s)
            cin >> row;
#ifdef LOCAL
        cout << "Init\n";
        for (auto &row : s)
            cout << row << '\n';
#else

#endif
        found = 0;
        if (!dfs(0, 0))
        {
            cout << 0 << '\n';
            return;
        }
        found = 0;
#ifdef LOCAL
        cout << "Mid\n";
        for (auto &row : s)
            cout << row << '\n';
#else

#endif
        if (!dfs(0, 0))
        {
            cout << 1 << '\n';
            return;
        }
#ifdef LOCAL
        cout << "Final\n";
        for (auto &row : s)
            cout << row << '\n';
#else

#endif
        cout << 2 << '\n';
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