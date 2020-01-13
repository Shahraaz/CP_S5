// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define MULTI_TEST
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

const int NAX = 2e5 + 5, MOD = 2000000007;

map<int, int> ls;

int get(vector<pair<int, int>> &a)
{
    int cnt = 0, l = -MOD, r = -MOD;
    sort(all(a));
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i].f > r)
        {
            if (r != -MOD)
                ls[l] = 0;
            ++cnt;
            l = a[i].f, r = a[i].s;
        }
        else
            r = max(r, a[i].s);
    }
    ls[l] = 0;
    return cnt;
}

void process(vector<pair<int, pair<int, int>>> &qr, vector<int> &ans)
{
    db("Process");
    set<int> open;
    for (int i = 0; i < qr.size(); i++)
    {
        vector<int> op, cl;
        int j = i - 1;
        while (j + 1 < int(qr.size()) && qr[j + 1].f == qr[i].f)
        {
            ++j;
            if (qr[j].s.f == 1)
                op.pb(qr[j].s.s);
            else
                cl.pb(qr[j].s.s);
        }
        db(i);
        pc(op, cl, open, ls);
        if (open.size() == 1 && !op.empty())
            ++ans[*open.begin()];
        for (auto &it : op)
            open.insert(it);
        for (auto &it : cl)
            open.erase(it);
        i = j;
    }
}

void solveCase(int caseNo)
{
    int n;
    cin >> n;
    vector<pair<int, int>> seg(n);
    vector<pair<int, pair<int, int>>> qr;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        seg[i] = {x, y};
        qr.pb({x, {1, i}});
        qr.pb({y, {-1, i}});
    }
    sort(all(qr));

    vector<int> ans(n);
    ls.clear();
    int cur = get(seg);
    
    process(qr, ans);
    for (int i = 0; i < n; i++)
        if (ls.count(seg[i].f))
            ++ls[seg[i].f];
    for (int i = 0; i < n; i++)
        if (ls[seg[i].f] == 1)
            --ans[i];
    cout << *max_element(all(ans)) + cur << '\n';
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
