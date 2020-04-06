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
        if (n == 1 && m == 1)
            return;
        pair<int, int> dest;
        vector<string> mp(n + 1, string(m + 2, '.'));
        for (size_t i = 1; i <= n; i++)
        {
            cin >> mp[i];
            mp[i] = '$' + mp[i];
            for (size_t j = 1; j <= m; j++)
            {
                if (mp[i][j] == 'F')
                    dest = {i, j};
            }
        }
        vector<vector<int>> dist(n + 1, vector<int>(m + 2, MOD));
        pair<int, int> curr;
        curr = {1, 1};
        bool rightFault = false;
        bool UpFault = false;

        auto goLeft = [&]() -> pair<int, int> {
            if (rightFault)
                cout << "R" << endl;
            else
                cout << "L" << endl;
            int x, y;
            cin >> x >> y;
            return curr = {x, y};
        };

        auto goRight = [&]() -> pair<int, int> {
            if (rightFault)
                cout << "L" << endl;
            else
                cout << "R" << endl;
            int x, y;
            cin >> x >> y;
            return curr = {x, y};
        };

        auto goUp = [&]() -> pair<int, int> {
            if (UpFault)
                cout << "D" << endl;
            else
                cout << "U" << endl;
            int x, y;
            cin >> x >> y;
            return curr = {x, y};
        };

        auto goDown = [&]() -> pair<int, int> {
            if (UpFault)
                cout << "U" << endl;
            else
                cout << "D" << endl;
            int x, y;
            cin >> x >> y;
            return curr = {x, y};
        };
        if (m >= 2 && mp[1][2] == '.')
        {
            goRight();
            if (curr.s == 1)
                rightFault = true;
            else
                goLeft();
            if (n == 1)
            {
                for (size_t i = 0; i < m; i++)
                    goRight();
                return;
            }
            vector<int> find(m + 1);
            for (size_t i = 1; i <= m; i++)
            {
                if (mp[2][i] != '*')
                {
                    goDown();
                    if (curr.f == 1)
                        UpFault = true;
                    break;
                }
                goRight();
            }
        }
        else
        {
            goDown();
            if (curr.f == 1)
                UpFault = true;
            else
                goUp();
            if (m == 1)
            {
                for (size_t i = 0; i < n; i++)
                    goDown();
                return;
            }
            vector<int> find(n + 1);
            for (size_t i = 1; i <= n; i++)
            {
                if (mp[i][2] != '*')
                {
                    goRight();
                    if (curr.s == 1)
                        rightFault = true;
                    break;
                }
                goDown();
            }
        }
        queue<pair<int, int>> Q;
        Q.push(dest);
        dist[dest.f][dest.s] = 0;
        auto isValid = [&](int x, int y) {
            if (1 <= x && x <= n && 1 <= y && y <= m)
                return mp[x][y] != '*';
            return false;
        };
        int a[] = {0, 0, 1, -1};
        int b[] = {1, -1, 0, 0};
        db(dest);
        while (!Q.empty())
        {
            auto x = Q.front().f;
            auto y = Q.front().s;
            Q.pop();
            if (dist[x][y] >= MOD)
                continue;
            db(x, y, dist[x][y]);
            for (size_t i = 0; i < 4; i++)
            {
                int x1 = x + a[i];
                int y1 = y + b[i];
                if (isValid(x1, y1) && dist[x1][y1] == MOD)
                {
                    // vis[x1][y1] = '*';
                    dist[x1][y1] = dist[x][y] + 1;
                    Q.push({x1, y1});
                }
            }
        }
        db("AfterDeterm", UpFault, rightFault);
        // return;
        while (dist[curr.f][curr.s] > 0)
        {
            db(curr, dist[curr.f][curr.s]);
            for (size_t i = 0; i < 4; i++)
            {
                int x1 = curr.f + a[i];
                int y1 = curr.s + b[i];
                db(i, x1, y1, dist[x1][y1]);
                if (isValid(x1, y1) && (dist[x1][y1] + 1) == dist[curr.f][curr.s])
                {
                    switch (i)
                    {
                    case 0:
                        goRight();
                        break;
                    case 1:
                        goLeft();
                        break;
                    case 2:
                        goDown();
                        break;
                    case 3:
                        goUp();
                        break;
                    default:
                        break;
                    }
                    curr = {x1, y1};
                    break;
                }
            }
        }
    }
};

int32_t main()
{
#ifndef LOCAL
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
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