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

vector<int> ciel, atk, def;

int partial()
{
    db("partialStart");
    int n = min(atk.size(), ciel.size());
    int ans = 0;
    for (int i = 0; i < n; i++)
        if (atk[i] < ciel[ciel.size() - 1 - i])
            ans += ciel[ciel.size() - 1 - i] - atk[i];
    db("partialEnd");
    return ans;
}

bool used[110];

int search(int x)
{
    int i = 0;
    for (int i = 0; i < ciel.size(); i++)
        if (ciel[i] >= x && !used[i])
        {
            used[i] = true;
            return i;
        }
    return -1;
}

int All()
{
    db("AllStart");
    int defSum = 0;
    for (int i = 0; i < def.size(); i++)
    {
        int x = search(def[i] + 1);
        if (x == -1)
            return 0;
        defSum += ciel[x];
    }
    for (int i = 0; i < atk.size(); i++)
    {
        int x = search(atk[i]);
        if (x == -1)
            return 0;
    }
    int ans = 0;
    for (int i = 0; i < ciel.size(); i++)
        ans += ciel[i];
    for (int i = 0; i < atk.size(); i++)
        ans -= atk[i];
    db("AllEnd");
    return ans - defSum;
}

void solveCase(int caseNo)
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        string type;
        int x;
        cin >> type >> x;
        if (type == "ATK")
            atk.pb(x);
        else
            def.pb(x);
    }
    for (int i = 0; i < m; i++)
    {
        int x;
        cin >> x;
        ciel.pb(x);
    }
    db("inpDone");
    sort(all(atk));
    sort(all(def));
    sort(all(ciel));
    db("SortDone");

    cout << max(partial(), All()) << '\n';
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
