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

using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;

class Solution
{
private:
    string s1, s2;
    int n, t;

    bool check(int x, int lo, int hi)
    {
        return lo <= x && x <= hi;
    }

    char select(char a, char b)
    {
        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            if (ch == a || ch == b)
                continue;
            return ch;
        }
        return 'a';
    }

    void print(int a, int b, int c, int d, int e)
    {
        for (size_t i = 0; i < n; i++)
        {
            if (s1[i] == s2[i])
            {
                if (d > 0)
                {
                    cout << s1[i];
                    --d;
                }
                else if (e > 0)
                {
                    cout << select(s1[i], s2[i]);
                    --e;
                }
            }
            else
            {
                if (a > 0)
                {
                    cout << s1[i];
                    --a;
                }
                else if (b > 0)
                {
                    cout << s2[i];
                    --b;
                }
                else
                {
                    cout << select(s1[i], s2[i]);
                    --c;
                }
            }
        }
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n >> t >> s1 >> s2;
        int x, y;
        x = y = 0;
        for (size_t i = 0; i < n; i++)
        {
            if (s1[i] == s2[i])
                x++;
            else
                y++;
        }
        for (int a = 0; a <= y; a++)
        {
            int e = t - y + a;
            if (check(e, 0, x))
            {
                int d = x - e;
                int b = a;
                int c = y - a - b;
                if (check(d, 0, x) && check(a, 0, y) && check(b, 0, y) && check(c, 0, y))
                {
                    print(a, b, c, d, e);
                    exit(0);
                }
            }
        }
        cout << -1 << '\n';
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