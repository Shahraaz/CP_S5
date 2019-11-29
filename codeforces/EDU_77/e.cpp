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
using Type = pair<int, int>;
using pbds = tree<Type, null_type, less<Type>, rb_tree_tag, tree_order_statistics_node_update>;
#define f first
#define s second
#define pb push_back
auto TimeStart = chrono::steady_clock::now();

const ll INF = 1e18;
const int NAX = 2e5 + 10, MOD = 1000000007, LOGN = 20, N = (1 << LOGN) + 100;
int n, sum[100], a[N];
ll dp[LOGN + 2][N];

ll solve(int cnt, int pos)
{
    ll &res = dp[cnt][pos];
    if (res >= 0)
        return res;
    if (a[pos] == -1)
        return res = 0;
    int rem = sum[cnt] - pos;
    db(rem, cnt, sum[cnt], pos);
    res = INF;
    if (cnt < LOGN)
        res = solve(cnt + 1, pos + 1) + a[pos];
    if (rem > 0)
        res = min(res, solve(cnt, pos + 1));
    return res;
}

void solveCase(int caseNo)
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    reverse(a, a + n);
    for (int i = 1, x = n / 2; i < 100; ++i, x /= 2)
        sum[i] = sum[i - 1] + x;
    memset(dp, -1, sizeof dp);
    cout << solve(0, 0) << '\n';
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
    for (int i = 0; i < t; ++i)
        solveCase(i);
#ifdef TIME
    cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
    return 0;
}