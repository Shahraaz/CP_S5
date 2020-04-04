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
    char getRandChar()
    {
        bool b = Random<int>{0, 1}(rng);
        if (b)
            return 'a' + Random<int>{0, 25}(rng);
        return 'A' + Random<int>{0, 25}(rng);
    }
    void solve(int x)
    {
        vector<vector<char>> matrix(x, vector<char>(x, '.'));
        vector<int> row(x), col(x);
        function<bool(int, int)> s = [&](int a, int b) -> bool {
            if (a == x || b == x)
            {
                // db(a, b, x);
                if (b == x)
                {
                    // pc(row, col);
                    // if (row[0] != 3)
                    for (size_t i = 0; i < x; i++)
                        if (row[i] == row[0] && row[0] == col[i])
                            ;
                        else
                            return false;
                    return true;
                }
                return s(0, b + 1);
            }
            auto prev = matrix[a][b];
            if (prev != '.')
                return s(a + 1, b);
            if (b + 1 < x)
            {
                if (matrix[a][b + 1] == '.')
                {
                    matrix[a][b + 1] = matrix[a][b] = getRandChar();
                    row[a]++;
                    col[b]++;
                    col[b + 1]++;
                    if (col[b] <= 3 && col[b + 1] <= 3 && row[a] <= 3)
                        if (s(a + 1, b))
                            return true;
                    matrix[a][b + 1] = matrix[a][b] = '.';
                    row[a]--;
                    col[b]--;
                    col[b + 1]--;
                }
            }
            if (a + 1 < x)
            {
                if (matrix[a + 1][b] == '.')
                {
                    matrix[a + 1][b] = matrix[a][b] = getRandChar();
                    row[a]++;
                    row[a + 1]++;
                    col[b]++;
                    if (col[b] <= 3 && row[a] <= 3 && row[a + 1] <= 3)
                        if (s(a + 1, b))
                            return true;
                    matrix[a + 1][b] = matrix[a][b] = '.';
                    row[a]--;
                    row[a + 1]--;
                    col[b]--;
                }
            }
            return s(a + 1, b);
        };
        if (s(0, 0))
        {
            cout << "Success in finding matrix for x = " << x << '\n';
            for (size_t i = 0; i < x; i++)
            {
                for (size_t j = 0; j < x; j++)
                    cout << matrix[i][j];
                cout << '\n';
            }
            cout << '\n';
        }
        else
            cout << "Faliure in finding matrix for x = " << x << '\n';
    }

public:
    Solution()
    {
    }
    ~Solution() {}
    void solveCase()
    {
        // vector<int> cnts = {3, 4, 5, 7};
        // // vector<int> cnts = {3};
        // for (auto &x : cnts)
        //     solve(x);
        map<int, vector<string>> mp;
        mp[3] = {"aab",
                 "c.b",
                 "cdd"};
        mp[4] = {"aabc",
                 "ddbc",
                 "efgg",
                 "efhh"};
        mp[5] = {"yyeel",
                 "ggj.l",
                 "yyjbb",
                 "..gzg ",
                 "..gzg"};
        mp[7] = {"aaffoo.",
                 "iibb..t",
                 "uucc..t",
                 "....tps",
                 "....tps",
                 "....dbw",
                 "....dbw"};
        int x;
        cin >> x;
        vector<vector<char>> res(x, vector<char>(x, '.'));
        if (x == 2)
        {
            cout << -1 << '\n';
            return;
        }
        int pre = 0;
        function<void(int)> solve = [&](int x) {
            // assert(x >= 0);
            if (x == 0)
                return;
            for (auto &Y : mp)
            {
                if (Y.f == x)
                {
                    for (size_t i = 0; i < x; i++)
                        for (size_t j = 0; j < x; j++)
                            res[pre + i][pre + j] = Y.s[i][j];
                    pre += Y.f;
                    return;
                }
            }
            if (x % 3 == 0)
            {
                solve(3);
                solve(x - 3);
                return;
            }
            if (x % 3 == 1)
            {
                solve(5);
                solve(x - 5);
                return;
            }
            solve(4);
            solve(x - 4);
        };
        solve(x);
        for (size_t i = 0; i < x; i++)
        {
            for (size_t j = 0; j < x; j++)
                cout << res[i][j];
            cout << '\n';
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