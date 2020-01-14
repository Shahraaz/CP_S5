// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
#define pc(...) PC(#__VA_ARGS__, __VA_ARGS__);
template <typename T, typename U>
ostream &operator<<(ostream &out, const pair<T, U> &p)
{
    out << '[' << p.first << ", " << p.second << ']';
    return out;
}
template <typename Arg>
void PC(const char *name, Arg &&arg)
{
    while (*name == ',' || *name == ' ')
        name++;
    std::cerr << name << " { ";
    for (const auto &v : arg)
        cerr << v << ' ';
    cerr << " }\n";
}
template <typename Arg1, typename... Args>
void PC(const char *names, Arg1 &&arg1, Args &&... args)
{
    while (*names == ',' || *names == ' ')
        names++;
    const char *comma = strchr(names, ',');
    std::cerr.write(names, comma - names) << " { ";
    for (const auto &v : arg1)
        cerr << v << ' ';
    cerr << " }\n";
    PC(comma, args...);
}
template <typename Arg1>
void ZZ(const char *name, Arg1 &&arg1)
{
    std::cerr << name << " = " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void ZZ(const char *names, Arg1 &&arg1, Args &&... args)
{
    const char *comma = strchr(names + 1, ',');
    std::cerr.write(names, comma - names) << " = " << arg1;
    ZZ(comma, args...);
}
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

int a[4] = {0, 0, 1, -1};
int b[4] = {1, -1, 0, 0};
void solveCase(int caseNo)
{
    int r, c;
    cin >> r >> c;
    vector<string> maze(r);
    for (auto &row : maze)
        cin >> row;
    vector<vector<int>> dist(r, vector<int>(c, MOD));
    vector<vector<bool>> vis(r, vector<bool>(c, false));
    queue<pair<int, int>> Q;
    pair<int, int> ash;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (maze[i][j] == 'E')
            {
                Q.push({i, j});
                vis[i][j] = true;
                dist[i][j] = 0;
            }
            else if (maze[i][j] == 'S')
                ash = {i, j};
    while (!Q.empty())
    {
        auto x = Q.front().f;
        auto y = Q.front().s;
        Q.pop();
        for (int i = 0; i < 4; i++)
        {
            int x1 = x + a[i];
            int y1 = y + b[i];
            if (0 <= x1 && x1 < r)
                if (0 <= y1 && y1 < c)
                    if (maze[x1][y1] != 'T')
                    {
                        dist[x1][y1] = min(dist[x1][y1], dist[x][y] + 1);
                        if (!vis[x1][y1])
                        {
                            Q.push({x1, y1});
                            vis[x1][y1] = true;
                        }
                    }
        }
    }
    int res = 0;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (dist[i][j] <= dist[ash.f][ash.s])
                if ('0' <= maze[i][j] && maze[i][j] <= '9')
                    res += maze[i][j] - '0';
    cout << res << '\n';
}

int main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    for (int i = 1; i <= t; ++i)
    {
        solveCase(i);
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
