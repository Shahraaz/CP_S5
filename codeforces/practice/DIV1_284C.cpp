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

const int NAX = 1e3 + 5, MOD = 1000000007;

int last[NAX], cap[NAX], flow[NAX];
int to[NAX], _prev[NAX], used[NAX], level[NAX];

struct MaxFlow
{
    int V, E;
    MaxFlow(int n)
    {
        V = n, E = 0;
        for (int i = 0; i < n; i++)
            last[i] = -1;
    }
    void add_edge(int x, int y, int f)
    {

        db(x, y, f);

        cap[E] = f;
        flow[E] = 0;
        to[E] = y;
        _prev[E] = last[x];
        last[x] = E;
        E++;

        cap[E] = 0;
        flow[E] = 0;
        to[E] = x;
        _prev[E] = last[y];
        last[y] = E;
        E++;
    }

    bool bfs(int s, int t)
    {
        db("bfs", s, t);
        for (size_t i = 0; i < V; i++)
            level[i] = -1;
        queue<int> Q;
        Q.push(s);
        level[s] = 0;
        while (!Q.empty())
        {
            int x = Q.front();
            Q.pop();
            db(x);
            for (int i = last[x]; i >= 0; i = _prev[i])
            {
                // db(i);
                if (level[to[i]] == -1 && cap[i] > flow[i])
                {
                    Q.push(to[i]);
                    level[to[i]] = level[x] + 1;
                }
            }
        }
#ifdef LOCAL
        cout << "LEVELS\n";
        for (size_t i = 0; i < V; i++)
            cout << i << ' ' << level[i] << '\n';
        cout << "~LEVELS\n";
#endif
        db("bfs end");
        return level[t] != -1;
    }

    int dfs(int v, int t, int f)
    {
        db("dfs", v, t, f);
        if (v == t)
            return f;
        for (int i = used[v]; i >= 0; used[v] = i = _prev[i])
        {
            // db(i,to[i]);
            if (level[to[i]] > level[v] && cap[i] > flow[i])
            {
                int tmp = dfs(to[i], t, min(f, cap[i] - flow[i]));
                if (tmp > 0)
                {
                    flow[i] += tmp;
                    flow[i ^ 1] -= tmp;
                    return tmp;
                }
            }
        }
        db("dfsEnd");
        return 0;
    }

    int maxFlow(int s, int t)
    {
        int i;
        while (bfs(s, t))
        {
            db("a");
            for (size_t i = 0; i < V; i++)
                used[i] = last[i];
            db("b");
            while (true)
            {
                int temp = dfs(s, t, MOD);
                db("fromDfs", s, t, temp);
                if (temp == 0)
                    break;
            }
            db("c");
        }
        int ans = 0;
        for (int i = last[s]; i >= 0; i = _prev[i])
            ans += flow[i];
        return ans;
    }
};

void solveCase()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(m), b(m), x(n);
    for (size_t i = 0; i < n; i++)
        cin >> x[i];

    for (int i = 0; i < m; i++)
    {
        cin >> a[i] >> b[i];
        --a[i], --b[i];
        if (a[i] % 2 == 1)
            swap(a[i], b[i]);
    }

    set<int> s;
    for (size_t i = 0; i < n; i++)
    {
        int y = x[i];
        for (size_t d = 2; d * d <= y; d++)
            if (y % d == 0)
            {
                s.insert(d);
                while (y % d == 0)
                    y /= d;
            }
        if (y > 1)
            s.insert(y);
    }
    int ans = 0;
    for (auto &p : s)
    {
        MaxFlow mf(n + 2);
        db(p);
        for (size_t i = 0; i < n; i++)
        {
            int y = x[i], cnt = 0;
            while (y % p == 0)
            {
                y /= p;
                cnt++;
            }
            // db(i, x[i], cnt, p);
            if (i % 2 == 0)
                mf.add_edge(n, i, cnt);
            else
                mf.add_edge(i, n + 1, cnt);
        }
        for (size_t i = 0; i < m; i++)
            mf.add_edge(a[i], b[i], 100);
        auto temp = mf.maxFlow(n, n + 1);
        db("flow", p, temp);
        ans += temp;
    }
    cout << ans << '\n';
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
