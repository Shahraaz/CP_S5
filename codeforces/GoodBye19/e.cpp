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
int cnt[2][2];

void solveCase(int caseNo)
{
    int n;
    cin >> n;
    db(n);
    vector<pair<int, int>> Points(n);
    for (auto &x : Points)
    {
        cin >> x.f >> x.s;
        x.f += 1e6;
        x.s += 1e6;
    }
    db(n);
    while (true)
    {
        // db("a",n);
        // pc(Points);
        // db("a",n);
        // db("a",n);
        memset(cnt, 0, sizeof cnt);
        db("a", n);
        for (auto P : Points)
            cnt[P.f % 2][P.s % 2]++;
        db("b", n, cnt[0][0], cnt[0][1], cnt[1][0], cnt[1][1]);
        if ((cnt[0][0] + cnt[1][1]) > 0 && (cnt[1][0] + cnt[0][1]) > 0)
        {
            vector<int> res;
            for (int i = 0; i < n; ++i)
                if ((Points[i].f % 2 + Points[i].s % 2) % 2)
                    res.pb(i + 1);
            cout << res.size() << '\n';
            for (auto x : res)
                cout << x << ' ';
            cout << '\n';
            return;
        }
        db("One");
        if (cnt[0][0] > 0 && cnt[1][1] > 0)
        {
            vector<int> res;
            for (int i = 0; i < n; ++i)
                if ((Points[i].f % 2))
                    res.pb(i + 1);
            cout << res.size() << '\n';
            for (auto x : res)
                cout << x << ' ';
            cout << '\n';
            return;
        }
        db("Two");
        if (cnt[0][1] > 0 && cnt[1][0] > 0)
        {
            vector<int> res;
            for (int i = 0; i < n; ++i)
            {
                db(i, n);
                if ((Points[i].f % 2))
                    res.pb(i + 1);
            }
            cout << res.size() << '\n';
            for (auto x : res)
                cout << x << ' ';
            cout << '\n';
            return;
        }
        int x, y;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                if (cnt[i][j])
                    x = i, y = j;
        for (auto &P : Points)
        {
            P.f -= x;
            P.s -= y;
            P.f /= 2;
            P.s /= 2;
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
