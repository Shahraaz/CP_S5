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
        vector<string> matrix(n);
        for (auto &floor : matrix)
            cin >> floor;
        vector<int> oneCnt(n + 1);
        vector<int> dpFromLeft(n + 1, MOD);
        vector<int> dpFromRight(n + 1, MOD);
        vector<bool> goingUpIsMandatory(n + 1);
        for (int i = 0; i < n; i++)
        {
            if (i > 0)
                goingUpIsMandatory[i] = goingUpIsMandatory[i - 1] || oneCnt[i - 1];
            else
                goingUpIsMandatory[0] = false;
            oneCnt[i] = count(all(matrix[i]), '1');
            if (oneCnt[i])
            {
                int idx = 0;
                for (int j = 1; j <= m + 1; j++)
                    if (matrix[i][j] == '1')
                        idx = max(idx, j);
                if (goingUpIsMandatory[i])
                    dpFromLeft[i] = min(2 * idx + 1 + dpFromLeft[i - 1], m + 2 + dpFromRight[i - 1]);
                else
                    dpFromLeft[i] = idx;
                idx = 0;
                reverse(all(matrix[i]));
                for (int j = 1; j <= m + 1; j++)
                    if (matrix[i][j] == '1')
                        idx = max(idx, j);
                if (goingUpIsMandatory[i])
                    dpFromRight[i] = min(2 * idx + 1 + dpFromRight[i - 1], m + 2 + dpFromLeft[i - 1]);
                else
                    dpFromRight[i] = idx;
            }
            else
            {
                if (goingUpIsMandatory[i])
                {
                    dpFromLeft[i] = min(1 + dpFromLeft[i - 1], m + 2 + dpFromRight[i - 1]);
                    dpFromRight[i] = min(1 + dpFromRight[i - 1], m + 2 + dpFromLeft[i - 1]);
                }
                else
                {
                    dpFromLeft[i] = 0;
                    dpFromRight[i] = 0;
                }
            }
        }
        cout << dpFromLeft[n - 1] << '\n';
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
