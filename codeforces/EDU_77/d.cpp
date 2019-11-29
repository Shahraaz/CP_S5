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
int m, n, k, Time;
int a[nax];
pair<pair<int, int>, int> traps[nax];

bool Solve(int soldCnt)
{
    if (soldCnt == 0)
        return true;
    int maxAgil = a[soldCnt - 1];
    int rMax = 0, addTime = n + 1;
    for (int i = 0; i < k; ++i)
    {
        if (traps[i].s <= maxAgil)
            continue;
        if (traps[i].f.s <= rMax)
            continue;
        db(addTime);
        if (rMax < traps[i].f.f)
        {
            rMax = traps[i].f.s;
            addTime += 2 * (rMax - traps[i].f.f + 1);
        }
        else
        {
            addTime += 2 * (traps[i].f.s - rMax);
            rMax = traps[i].f.s;
        }
        db(rMax, i, addTime, traps[i]);
    }
    db(soldCnt, maxAgil, addTime, Time);
    return addTime <= Time;
}

void solve(int caseNo)
{
    db("Start");
    cin >> m >> n >> k >> Time;
    for (int i = 0; i < m; ++i)
        cin >> a[i];
    db("Start");
    sort(a, a + m);
    reverse(a, a + m);
    for (int i = 0; i < k; ++i)
        cin >> traps[i].f.f >> traps[i].f.s >> traps[i].s;
    db("Start");
    sort(traps, traps + k);
    int low = 0, high = m, ans = 0;
    db("Start");
    while (low <= high)
    {
        db(low, high);
        int mid = (low + high) / 2;
        if (Solve(mid))
            ans = mid, low = mid + 1;
        else
            high = mid - 1;
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