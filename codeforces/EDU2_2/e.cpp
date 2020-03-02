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

int clr[NAX];
vector<int> adj[NAX];
map<int, int> countClr[NAX];
ll sum[NAX];

class Solution
{
private:
    pair<int, pair<ll, int>> dfs(int node, int par)
    {
        int idx = node;
        ll sumOfResClr = clr[node];
        int countOfClr = 1;
        countClr[idx][clr[node]] = 1;
        ll sumFromChild = 0;
        for (auto &child : adj[node])
        {
            if (child == par)
                continue;
            auto tmep = dfs(child, node);
            int idxFromChild = tmep.f;
            ll sumOfResClrFromChild = tmep.s.f;
            sumFromChild += sumOfResClrFromChild;
            int countOfClrFromChild = tmep.s.s;
            if (countClr[idxFromChild].size() > countClr[idx].size())
            {
                swap(idx, idxFromChild);
                swap(sumOfResClr, sumOfResClrFromChild);
                swap(countOfClr, countOfClrFromChild);
            }
            for (auto &elem : countClr[idxFromChild])
            {
                countClr[idx][elem.f] += elem.s;
                if (countClr[idx][elem.f] > countOfClr)
                {
                    countOfClr = countClr[idx][elem.f];
                    sumOfResClr = elem.f;
                }
                else if (countClr[idx][elem.f] == countOfClr)
                {
                    sumOfResClr += elem.f;
                }
            }
        }
        sum[node] = sumOfResClr;
        db(node, sum[node]);
        return make_pair(idx, make_pair(sumOfResClr, countOfClr));
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> clr[i];
        }
        for (int i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            // --u, --v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        dfs(1, 1);
        for (int i = 1; i <= n; i++)
            cout << sum[i] << ' ';
        cout << '\n';
    }
};

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
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
