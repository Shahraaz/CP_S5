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

const int NAX = 1e5 + 10, MOD = 1000000007, LG = ceil(log2l(1e13)) + 1;

ll a[NAX];
int sz = 1;

struct node
{
    node *child[2];
    node()
    {
        child[0] = child[1] = nullptr;
    }
};

node *root;

void insert(ll x)
{
    node *curr = root;
    for (int i = LG; i >= 0; --i)
    {
        bool here = (x >> i) & (1);
        if (curr->child[here] == nullptr)
            curr->child[here] = new node;
        curr = curr->child[here];
    }
}

ll query(ll x)
{
    ll ret = 0;
    node *curr = root;
    for (int i = LG; i >= 0; --i)
    {
        bool here = (x >> i) & (1);
        ret *= 2;
        if (curr->child[1 - here] != nullptr)
        {
            curr = curr->child[1 - here];
            ret++;
        }
        else
            curr = curr->child[here];
    }
    return ret;
}

void solveCase(int caseNo)
{
    root = new node;
    int n;
    cin >> n;
    ll xorAll = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
        xorAll ^= a[i];
    }
    ll maxgot = 0;
    ll total = 0;
    insert(total);
    for (int i = 0; i < n; ++i)
    {
        total ^= a[i];
        insert(total);
        maxgot = max(maxgot, query(total ^ xorAll));
    }
    cout << maxgot << '\n';
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