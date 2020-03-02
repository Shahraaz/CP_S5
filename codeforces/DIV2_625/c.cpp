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

const int NAX = 1e2 + 5, MOD = 1000000007;

int canIBeClear[NAX][NAX][NAX][NAX];
int dpUndel[NAX];
int dpDel[NAX];

class Solution
{
private:
    int n;
    string str;

    bool check(int pos, int clc)
    {
        if (1 <= pos && pos <= n)
            if (1 <= clc && clc <= n)
                return abs(str[pos] - str[clc]) == 1;
        return false;
    }

    int count(int start, int End)
    {
        if (start < 1)
            start = 1;
        if (start > n)
            start = n;
        if (End < 1)
            End = 1;
        if (End > n)
            End = n;
        if (End < start)
            return 0;
        return End - start + 1;
    }

    int solveCanIBeClear(int start, int End, int prevUnc, int nextUnc)
    {
        int sz = count(start, End);
        if (sz <= 0)
            return 1;
        if (start > End || start < 1 || start > n || End < 1 || End > n)
            return 1;
        int &ret = canIBeClear[start][End][prevUnc][nextUnc];
        if (ret >= 0)
            return ret;
        ret = 0;
        for (int pos = start; pos <= End; pos++)
        {
            if (pos == start)
            {
                if (check(pos, prevUnc) && solveCanIBeClear(pos + 1, End, prevUnc, nextUnc))
                {
                    ret = 1;
                    break;
                }
            }
            if (pos == End)
            {
                if (check(pos, nextUnc) && solveCanIBeClear(start, pos - 1, prevUnc, nextUnc))
                {
                    ret = 1;
                    break;
                }
            }
            if (check(pos, pos - 1) && start <= (pos - 1) && (pos - 1) <= End)
                if (solveCanIBeClear(start, pos - 1, prevUnc, min(pos + 1, nextUnc)) && solveCanIBeClear(pos + 1, End, max(pos - 1, prevUnc), nextUnc))
                {
                    ret = 1;
                    break;
                }
            if (check(pos, pos + 1) && start <= (pos + 1) && (pos + 1) <= End)
                if (solveCanIBeClear(start, pos - 1, prevUnc, min(pos + 1, nextUnc)) && solveCanIBeClear(pos + 1, End, max(pos - 1, prevUnc), nextUnc))
                {
                    ret = 1;
                    break;
                }
        }
        db(start, End, prevUnc, nextUnc, ret);
        return ret;
    }

    int solveUndel(int pos)
    {
        if (pos >= n)
            return 0;
        int &ret = dpUndel[pos];
        if (ret >= 0)
            return ret;
        ret = max(solveUndel(pos + 1), solveDel(pos + 1));
        for (int nextPos = pos + 1; nextPos <= n; nextPos++)
            if ((str[pos] - str[nextPos]) == 1 || (str[pos] - str[nextPos]) == -1)
                if (solveCanIBeClear(pos + 1, nextPos - 1, pos, nextPos))
                    ret = max(ret, count(pos + 1, nextPos) + max(solveUndel(nextPos + 1), solveDel(nextPos + 1)));
        // db(pos, ret, "Un");
        return ret;
    }

    int solveDel(int pos)
    {
        if (pos >= n)
            return 0;
        int &ret = dpDel[pos];
        if (ret >= 0)
            return ret;
        ret = -MOD;
        for (int nextPos = pos + 1; nextPos <= n; nextPos++)
            if ((str[pos] - str[nextPos]) == 1 || (str[pos] - str[nextPos]) == -1)
                if (solveCanIBeClear(pos + 1, nextPos - 1, pos, nextPos))
                    ret = max(ret, count(pos, nextPos - 1) + max(solveUndel(nextPos), solveDel(nextPos)));
        // db(pos, ret, "Del");
        return ret;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n >> str;
        str = "$" + str + "$$";
        memset(dpUndel, -1, sizeof dpUndel);
        memset(dpDel, -1, sizeof dpDel);
        memset(canIBeClear, -1, sizeof canIBeClear);
        cout << max(solveUndel(1), solveDel(1)) << '\n';
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
