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

const int NAX = 2e5 + 10, MOD = 1000000007, LOG = 22;
ll MRG[LOG], IMRG[LOG];
vector<int> Tree[2 << LOG];
int a[1 << LOG];

void build(int node, int left, int right, int level = 1)
{
    db(node, left, right, level);
    if (left == right)
    {
        Tree[node].pb(a[left]);
        return;
    }
    int mid = (left + right) / 2;
    build(2 * node, left, mid, level + 1);
    build(2 * node + 1, mid + 1, right, level + 1);
    Tree[node] = Tree[2 * node];
    int j = 0, n = Tree[2 * node].size();
    for (auto elem : Tree[2 * node])
    {
        while ((j < n) && (Tree[2 * node + 1][j] < elem))
            ++j;
        MRG[level] += j;
    }
    j = 0;
    n = Tree[2 * node].size();
    for (auto elem : Tree[2 * node + 1])
    {
        while ((j < n) && (Tree[2 * node][j] < elem))
            ++j;
        IMRG[level] += j;
        Tree[node].pb(elem);
    }
    db(node, MRG[level], IMRG[level], level);
    sort(Tree[node].begin(), Tree[node].end());
    pc(Tree[node]);
}

bool mark[LOG];

void solveCase(int caseNo)
{
    int n;
    cin >> n;
    for (int i = 1; i <= (1 << n); ++i)
        cin >> a[i];
    build(1, 1, (1 << n));
    int q;
    cin >> q;
    while (q--)
    {
        int a;
        cin >> a;
        ll ans = 0;
        for (int i = n - a + 1; i <= (n + 1); ++i)
            mark[i] ^= 1;
        for (int i = 1; i <= (n + 1); ++i)
            ans += mark[i] ? IMRG[i] : MRG[i];
        cout << ans << '\n';
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
    for (int i = 0; i < t; ++i)
        solveCase(i);
#ifdef TIME
    cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
    return 0;
}