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

const int NAX = 2e5 + 5, MOD = 1000000007, k = 330;
int n, q, query, mark[NAX], col[NAX];
ll score[NAX], tot[NAX], a[NAX], sum[NAX];
vector<int> kh[k];

void paint(int id, int x, int y, int color)
{
    int l = id * k;
    int r = min((id + 1) * k, n);
    if (r <= l)
        return;
    if (x <= l && r <= y)
    {
        ll sc = abs(col[id] - color);
        score[id] += sc;
        col[id] = color;
        for (int i : kh[id])
        {
            ll t = tot[i];
            tot[i] -= sc;
            tot[i] += abs(color - a[i]);
            sum[id] += tot[i] - t;
        }
        kh[id].clear();
        return;
    }
    int L = max(l, x);
    int R = min(r, y);
    if (R - L < 1)
        return;
    for (int i : kh[id])
        mark[i] = query;
    for (int i = L; i < R; ++i)
    {
        int C;
        if (mark[i] == query)
            C = a[i];
        else
            C = col[id], kh[id].pb(i);
        a[i] = color;
        tot[i] += abs(color - C);
        sum[id] += abs(color - C);
    }
}

ll ask(int id, int x, int y)
{
    int l = id * k;
    int r = min((id + 1) * k, n);
    if (r <= l)
        return 0;
    if (x <= l && r <= y)
        return score[id] * (ll)(r - l) + sum[id];
    int L = max(l, x);
    int R = min(r, y);
    if (R - L < 1)
        return 0;
    ll ans = score[id] * ll(R - L);
    for (int i = L; i < R; ++i)
        ans += tot[i];
    return ans;
}

void solveCase(int caseNo)
{
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
    {
        a[i] = i + 1;
        kh[i / k].pb(i);
    }
    for (query = 0; query < q; query++)
    {
        int type, l, r, c;
        cin >> type >> l >> r;
        --l;
        if (type == 1)
        {
            cin >> c;
            for (int i = 0; i < (n / k + 2); i++)
                paint(i, l, r, c);
        }
        else
        {
            ll ans = 0;
            for (int i = 0; i < (n / k + 2); i++)
                ans += ask(i, l, r);
            cout << ans << '\n';
        }
    }
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
