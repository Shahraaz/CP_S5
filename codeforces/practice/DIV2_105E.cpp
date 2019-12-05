//Optimise
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
auto TimeStart = chrono::steady_clock::now();

const int NAX = 2e5 + 10, MOD = 1000000007;
int n, m;
vector<vector<int>> a, prefix, suffix, line;
vector<int> aLen;

void solveCase(int caseNo)
{
    cin >> n >> m;
    aLen.resize(n);
    a.resize(n);
    prefix.resize(n);
    suffix.resize(n);
    line.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> aLen[i];
        a[i].resize(aLen[i]);
        prefix[i].resize(aLen[i] + 1);
        suffix[i].resize(aLen[i] + 1);
        line[i].resize(aLen[i] + 1);
        for (auto &x : a[i])
            cin >> x;
        for (int j = 0; j < aLen[i]; ++j)
        {
            prefix[i][j + 1] = prefix[i][j] + a[i][j];
            suffix[i][j + 1] = suffix[i][j] + a[i][aLen[i] - 1 - j];
        }
        for (int x = 0; x <= aLen[i]; ++x)
            for (int y = 0; x + y <= aLen[i]; ++y)
                line[i][x + y] = max(line[i][x + y], prefix[i][x] + suffix[i][y]);
    }
    vector<int> dp[2];
    dp[0].resize(m + 1);
    dp[1].resize(m + 1);
    bool curr = false, prev = true;
    for (int i = 0; i <= min(aLen[0], m); ++i)
        dp[curr][i] = max(dp[curr][i], line[0][i]);
    swap(curr, prev);
    for (int i = 1; i < n; ++i, swap(curr, prev))
        for (int j = 0; j <= m; ++j)
            for (int k = 0; k <= aLen[i] && j + k <= m; ++k)
                dp[curr][j + k] = max(dp[curr][j + k], dp[prev][j] + line[i][k]);
    cout << dp[prev][m] << '\n';
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