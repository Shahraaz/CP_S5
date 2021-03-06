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

const int NAX = 3e5 + 5, MOD = 1000000007;

vector<pair<int, pair<int, int>>> q;
int n, m, a[NAX], mnvl[NAX], mxvl[NAX];
int st[4 * NAX], used[NAX];

void solveCase()
{
    cin >> n >> m;
    ordered_set<int> s;
    map<int, vector<int>> idv;
    db("a");
    for (int i = 1; i <= m; i++)
    {
        cin >> a[i];
        if (!idv.count(a[i]))
        {
            int totalElements = s.size();
            int smallerElements = s.order_of_key(a[i]);
            int greaterElements = totalElements - smallerElements;
            mxvl[a[i]] = greaterElements + a[i];
        }
        s.insert(a[i]);
        idv[a[i]].pb(i);
    }
    db("b");
    for (int i = 1; i <= n; i++)
    {
        if (s.find(i) != s.end())
            mnvl[i] = 1;
        else
        {
            int totalElements = s.size();
            auto smallerElements = s.order_of_key(a[i]);
            auto greaterElements = totalElements - smallerElements;
            mxvl[a[i]] = greaterElements + a[i];
            mnvl[i] = i;
        }
    }
    db("c");
    s.clear();
    for (int i = m; i >= 1; i--)
    {
        if (idv[a[i]].back() == i)
        {
            int sz = s.size();
            mxvl[a[i]] = max(mxvl[a[i]], sz + 1);
        }
        s.insert(a[i]);
    }
    db("d");
    for (auto &el : idv)
    {
        for (size_t i = 0; i + 1 < el.s.size(); i++)
            q.pb({el.s[i], {el.s[i + 1], el.f}});
    }
    db("e");
    sort(all(q), [&](pair<int, pair<int, int>> A, pair<int, pair<int, int>> B) -> bool {
        if (A.s.f != B.s.f)
            return A.s.f < B.s.f;
        return A.f < B.f;
    });
    db("f");
    int j = 1;
    function<void(int, int, int, int, int)> update = [&update](int node, int l, int r, int x, int d) -> void {
        if (l == r)
        {
            st[node] = d;
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid)
            update(2 * node, l, mid, x, d);
        else
            update(2 * node + 1, l, mid, x, d);
        st[node] = st[2 * node] + st[2 * node + 1];
    };
    db("g");
    function<int(int, int, int, int, int)> find = [&find](int node, int A, int B, int l, int r) -> int {
        if (l > B || r < A)
            return 0;
        if (A <= l && r <= B)
            return st[node];
        int mid = (l + r) / 2;
        return find(2 * node, A, B, l, mid) + find(2 * node + 1, A, B, mid + 1, r);
    };
    db("h");
    for (int i = 1; i <= n; i++)
        cout << mnvl[i] << ' ' << mxvl[i] << '\n';
    pc(q);
    for (size_t i = 0; i < q.size(); i++)
    {
        while (j <= q[i].s.f)
        {
            if (!used[a[j]])
            {
                update(1, 1, m, j, 1);
                used[a[j]] = j;
            }
            else
            {
                update(1, 1, m, used[a[j]], 0);
                update(1, 1, m, j, 1);
                used[a[j]] = j;
            }
            ++j;
        }
        int diff = find(1, 1, m, q[i].f, q[i].s.f);
        db(q[i], diff);
        mxvl[q[i].s.s] = max(mxvl[q[i].s.s], diff);
    }
    db("i");
    for (int i = 1; i <= n; i++)
        cout << mnvl[i] << ' ' << mxvl[i] << '\n';
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
        solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
