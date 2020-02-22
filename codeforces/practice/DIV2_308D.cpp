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

void solveCase()
{
    using point = complex<long long>;
    int n;
    cin >> n;
    vector<point> polygon(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        polygon[i] = point(x, y);
    }
    if (n == 1)
    {
        cout << 0 << '\n';
        return;
    }
    ll ans = 0;
    auto getPhase = [](point &a, point &b) -> pair<ll, ll> {
        ll dx = a.real() - b.real();
        ll dy = a.imag() - b.imag();
        ll gcd = __gcd(abs(dx), abs(dy));
        // if (dx == 0 || dy == 0)
        //     db(dx, dy, gcd);
        dx /= gcd;
        dy /= gcd;
        if (dy < 0)
        {
            dx *= -1;
            dy *= -1;
        }
        else if (dy == 0)
        {
            if (dx < 0)
                dx *= -1;
        }
        // if (dx == 0 || dy == 0)
        //     db(dx, dy, gcd);
        return make_pair(dx, dy);
    };
    for (int i = 0; i < n; i++)
    {
        vector<pair<ll, ll>> angles;
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            angles.pb(getPhase(polygon[j], polygon[i]));
        }
        // db(i);
        sort(all(angles));
        // pc(angles);
        for (auto it = angles.begin(); it != angles.end();)
        {
            auto up = upper_bound(all(angles), *it);
            ll cnt = up - it;
            ans += cnt * (n - cnt - 1);
            it = up;
        }
    }
    cout << ans / 6 << '\n';
}

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
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
