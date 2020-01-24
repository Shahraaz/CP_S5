// Optimise
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
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;

pair<long long, string> solve(ll a, int curr)
{
    if (a == 0)
        return {0, ""};
    else if (a < 0)
        return {INT_MAX, ""};
    else if (curr == 20)
        return {INT_MAX, ""};
    auto increase = solve(a + curr, curr + 1);
    auto decrease = solve(a - curr, curr + 1);
    if (increase.f <= decrease.f)
    {
        return {increase.f + 1, "-" + to_string(curr) + increase.s};
    }
    else if (increase.f > decrease.f)
    {
        return {decrease.f + 1, "+" + to_string(curr) + decrease.s};
    }
    // else
    // {
    //     db(a, "increase/decrease", curr);
    //     return decrease + 1;
    // }
}

bool ok(int res, int d)
{
    ll sum = res * (ll)(res + 1) / 2;
    if (sum < d)
        return false;
    return sum % 2 == d % 2;
}

void solveCase(int caseNo)
{
    ll a, b;
    cin >> a >> b;
    // a = Random<int>{0, 100}(rng);
    // b = Random<int>{a, 100}(rng);
    ll diff = abs(a - b);
    // auto ans = solve(diff, 1);
    // cout << ans.f << ' ' << diff << ' ' << (ans.f * (ans.f + 1)) / 2 << ' ' << ans.s << '\n';
    if (diff == 0)
    {
        cout << "0\n";
        return;
    }
    int res = sqrtl(diff);
    while (!ok(res, diff))
        ++res;
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
        // cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        // TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
