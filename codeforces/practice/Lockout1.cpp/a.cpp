// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

class Solution
{
private:
    bool check(vector<vector<char>> &grid)
    {
        int n = grid.size(), m = grid[0].size();
        if (n % 3 == 0)
        {
            int n3 = n / 3;
            set<char> s;
            for (size_t i = 0; i < n3; i++)
                for (size_t j = 0; j < m; j++)
                    s.insert(grid[i][j]);
            if (s.size() > 1)
                return false;
            set<char> s1;
            for (size_t i = 0; i < n3; i++)
                for (size_t j = 0; j < m; j++)
                    s1.insert(grid[i + n3][j]);
            if (s1.size() > 1)
                return false;
            set<char> s2;
            for (size_t i = 0; i < n3; i++)
                for (size_t j = 0; j < m; j++)
                    s2.insert(grid[i + 2 * n3][j]);
            if (s2.size() > 1)
                return false;
        }
        return false;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        vector<vector<char>> grid(n, vector<char>(m));
        vector<vector<char>> grid2(m, vector<char>(n));
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < m; j++)
            {
                cin >> grid[i][j];
                grid2[j][i] = grid[i][j];
            }
        }
        check(grid);
        check(grid2);
        cout << "NO\n";
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
