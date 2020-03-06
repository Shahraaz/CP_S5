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

const int NAX = 2e3 + 5, MOD = 1000000007;

int vis[NAX][NAX];
int maxLCnt[NAX][NAX];
int maxRCnt[NAX][NAX];
int a[] = {0, 0, 1, -1};
int b[] = {1, -1, 0, 0};

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
        int r, c;
        cin >> r >> c;
        int x, y;
        cin >> x >> y;
        memset(vis, 0, sizeof vis);
        queue<pair<pair<int, int>, pair<int, int>>> Q;
        Q.push({{r - 1, c - 1}, {x, y}});
        vis[r - 1][c - 1] = true;
        auto isValid = [&n, &m](int x, int y) {
            return 0 <= x && x < n && 0 <= y && y < m;
        };
        vector<string> myMap(n);
        for (auto &x : myMap)
            cin >> x;
        maxLCnt[r - 1][c - 1] = x;
        maxRCnt[r - 1][c - 1] = y;
        while (!Q.empty())
        {
            auto top = Q.front();
            Q.pop();
            top.s.f = maxLCnt[top.f.f][top.f.s];
            top.s.s = maxRCnt[top.f.f][top.f.s];
            db(top);
            for (int j = top.f.f + 1; j < n; j++)
            {
                if (isValid(j, top.f.s) && myMap[j][top.f.s] == '.')
                {
                    if (!vis[j][top.f.s])
                    {
                        vis[j][top.f.s] = true;
                        maxLCnt[j][top.f.s] = max(maxLCnt[j][top.f.s], top.s.f);
                        maxRCnt[j][top.f.s] = max(maxRCnt[j][top.f.s], top.s.s);
                        Q.push({{j, top.f.s}, {top.s.f, top.s.s}});
                    }
                    maxLCnt[j][top.f.s] = max(maxLCnt[j][top.f.s], top.s.f);
                    maxRCnt[j][top.f.s] = max(maxRCnt[j][top.f.s], top.s.s);
                }
                else
                    break;
            }
            for (int j = top.f.f - 1; j >= 0; j++)
            {
                if (isValid(j, top.f.s) && myMap[j][top.f.s] == '.')
                {
                    if (!vis[j][top.f.s])
                    {
                        vis[j][top.f.s] = true;
                        maxLCnt[j][top.f.s] = max(maxLCnt[j][top.f.s], top.s.f);
                        maxRCnt[j][top.f.s] = max(maxRCnt[j][top.f.s], top.s.s);
                        Q.push({{j, top.f.s}, {top.s.f, top.s.s}});
                    }
                    maxLCnt[j][top.f.s] = max(maxLCnt[j][top.f.s], top.s.f);
                    maxRCnt[j][top.f.s] = max(maxRCnt[j][top.f.s], top.s.s);
                }
                else
                    break;
            }
            if (isValid(top.f.f, top.f.s - 1) && top.s.f > 0)
            {
                if (!vis[top.f.f][top.f.s - 1])
                    if (myMap[top.f.f][top.f.s - 1] == '.')
                    {
                        vis[top.f.f][top.f.s - 1] = true;
                        Q.push({{top.f.f, top.f.s - 1}, {top.s.f - 1, top.s.s}});
                    }
                maxLCnt[top.f.f][top.f.s - 1] = max(maxLCnt[top.f.f][top.f.s - 1], top.s.f - 1);
                maxRCnt[top.f.f][top.f.s - 1] = max(maxRCnt[top.f.f][top.f.s - 1], top.s.s);
            }
            if (isValid(top.f.f, top.f.s + 1) && top.s.s > 0)
            {
                if (!vis[top.f.f][top.f.s + 1])
                    if (myMap[top.f.f][top.f.s + 1] == '.')
                    {
                        vis[top.f.f][top.f.s + 1] = true;
                        Q.push({{top.f.f, top.f.s + 1}, {top.s.f, top.s.s - 1}});
                    }
                maxLCnt[top.f.f][top.f.s + 1] = max(maxLCnt[top.f.f][top.f.s + 1], top.s.f);
                maxRCnt[top.f.f][top.f.s + 1] = max(maxRCnt[top.f.f][top.f.s + 1], top.s.s - 1);
            }
        }
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << vis[i][j];
                res += vis[i][j];
            }
            cout << '\n';
        }

        cout << res << '\n';
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
