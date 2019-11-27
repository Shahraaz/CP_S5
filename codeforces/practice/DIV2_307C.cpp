//Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define multitest 1
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
using T = pair<int, int>;
using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define f first
#define s second
#define pb push_back
auto TimeStart = chrono::steady_clock::now();

const int nax = 2e5 + 10, mod = 1000000007;
int n, m;
vector<int> arr;

bool Solve(ll time)
{
    int pos = n;
    auto brr = arr;
    for (int i = 0; i < m; ++i)
    {
        ll Time = time;
        while (pos > 0 && brr[pos] == 0)
            pos--;
        if (pos < 1)
            return true;
        Time -= pos;
        if (Time <= 0)
            return false;
        while (pos > 0 && brr[pos] <= Time)
        {
            Time -= brr[pos];
            brr[pos] = 0;
            pos--;
        }
        if (pos > 0 && Time > 0)
            brr[pos] -= Time;
    }
    return pos < 1;
}

void solve(int caseNo)
{
    cin >> n >> m;
    arr.resize(n + 1);
    ll low = 0, high = n, ans;
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];
        high += arr[i];
    }
    ans = high;
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        if (Solve(mid))
            ans = mid, high = mid - 1;
        else
            low = mid + 1;
    }
    cout << ans << '\n';
}

int main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef multitest
    cin >> t;
#endif
    for (int i = 0; i < t; ++i)
        solve(i);
#ifdef TIME
    cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
    return 0;
}