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

const int NAX = 1e2 + 10, MOD = 1000000007;
string a, b, virus;
vector<int> lps;
int cache[NAX][NAX][NAX][2], p, q, r;

vector<int> compute_lps(string s)
{
    int n = s.size();
    vector<int> lps(n);
    for (int i = 1; i < n; ++i)
    {
        int j = lps[i - 1];
        while (j > 0 && s[i] != s[j])
            j = lps[j - 1];
        if (s[i] == s[j])
            ++j;
        lps[i] = j;
    }
    return lps;
}

int dp(int i, int j, int k, int ongoing)
{
    if (k == r)
        return -MOD;
    if (i == p || j == q)
        return 0;
    int &ret = cache[i][j][k][2];
    if (ret >= 0)
        return ret;
    ret = 0;
    if (!ongoing)
        ret = max(dp(i + 1, j, k, 0), dp(i, j + 1, k, 0));
    if (a[i] == b[j])
    {
        if (a[i] == virus[k])
            ret = max(ret, 1 + dp(i + 1, j + 1, k + 1, 0));
        else
        {
            if (k == 0)
                ret = max(ret, 1 + dp(i + 1, j + 1, 0, 0));
            else
                ret = max(ret,dp(i, j, lps[k - 1], 1));
        }
    }
    return ret;
}

void path(int i, int j, int k, int ongoing)
{
    if (i == p || j == q)
        return;
    int ans = dp(i, j, k, ongoing);
    if (ans == 0)
        return;
    if (!ongoing)
    {
        if (ans == dp(i + 1, j, k, 0))
            return path(i + 1, j, k, 0);
        if (ans == dp(i, j + 1, k, 0))
            return path(i, j + 1, k, 0);
    }
    if (a[i] == b[j])
    {
        if (a[i] == virus[k])
        {
            cout << a[i];
            if (ans == (1 + dp(i + 1, j + 1, k + 1, 0)))
                return path(i + 1, j + 1, k + 1, 0);
        }
        else
        {
            if (k == 0)
            {
                cout << a[i];
                return path(i + 1, j + 1, 0, 0);
            }
            else
                return path(i, j, lps[k - 1], 1);
        }
    }
}

void solveCase(int caseNo)
{
    memset(cache, -1, sizeof cache);
    cin >> a >> b >> virus;
    p = a.size(), q = b.size(), r = virus.size();
    lps = compute_lps(virus);
    int ans = dp(0, 0, 0, 0);
    if (ans == 0)
        cout << ans << '\n';
    else
        path(0, 0, 0, 0);
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