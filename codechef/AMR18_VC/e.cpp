//Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define MULTI_TEST
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
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;

int exist[101][10000];
string ans[101][10000];

bool fn(int n, int k)
{
    if (n < 0 || k < 0)
        return false;
    if (n == 0 && k == 0)
        return true;
    else if (k > (n * (n + 1) / 2) || k < n)
        return false;
    else if (exist[n][k] >= 0)
        return exist[n][k];
    else
    {
        exist[n][k] = false;
        for (int iter = 1; iter <= n; ++iter)
        {
            if (fn(n - iter, k - iter * (iter + 1) / 2))
            {
                exist[n][k] = true;
                for (int j = 0; j < iter - 1; ++j)
                    ans[n][k] += "()";
                ans[n][k] += '(';
                ans[n][k] += ans[n - iter][k - iter * (iter + 1) / 2];
                ans[n][k] += ')';
                db(n,k,ans[n][k]);
                return true;
            }
        }
    }
    return exist[n][k];
}

void solveCase(int caseNo)
{
    // BALSUB
    int n, k;
    cin >> n >> k;
    if (n & 1)
        cout << "impossible\n";
    else if (fn(n / 2, k))
    {
        db(exist[n / 2][k]);
        cout << ans[n / 2][k] << '\n';
    }
    else
        cout << "impossible\n";
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
    memset(exist, -1, sizeof exist);
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