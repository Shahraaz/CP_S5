//Optimise
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
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;

string s;
using ld = long double;
auto pi = acosl(-1);

struct posVec
{
    int rot[3];
    int head;
    posVec()
    {
        head = rot[1] = rot[2] = 0;
        rot[0] = 1;
    };
    void rotate()
    {
        head = head + 1;
        if (head == 6)
            head = 0;
        int re = -rot[2];
        rot[2] = rot[1];
        rot[1] = rot[0];
        rot[0] = re;
    }
};

posVec merge(posVec a, posVec b)
{
    for (int i = 0; i < a.head; ++i)
        b.rotate();
    posVec ret;
    ret.head = b.head;
    for (int i = 0; i < 3; ++i)
        ret.rot[i] = a.rot[i] + b.rot[i];
    return ret;
}

posVec Tree[NAX * 4];

void build(int node, int start, int end)
{
    if (start > end)
        return;
    if (start == end)
    {
        Tree[node] = posVec();
        for (int j = 0; j < s[start] - '0'; ++j)
            Tree[node].rotate();
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    Tree[node] = merge(Tree[2 * node], Tree[2 * node + 1]);
}

posVec query(int node, int start, int end, int qstart, int qend)
{
    if (start > end || qend < start || end < qstart)
    {
        auto ret = posVec();
        ret.rot[0] = 0;
        return ret;
    }
    if (qstart <= start && end <= qend)
        return Tree[node];
    int mid = (start + end) / 2;
    return merge(query(2 * node, start, mid, qstart, qend), query(2 * node + 1, mid + 1, end, qstart, qend));
}

void solveCase(int caseNo)
{
    // ROBOTS
    int n, m;
    int l, r;
    cin >> n >> m;
    cin >> s;
    build(1, 0, n - 1);
    while (m--)
    {
        cin >> l >> r;
        --l, --r;
        auto ret = query(1, 0, n - 1, l, r);
        ld y = sqrtl(3) / 2, x = 1 / (ld)2;
        x *= 2 * ret.rot[0] + ret.rot[1] - ret.rot[2];
        y *= ret.rot[1] + ret.rot[2];
        cout << fixed << setprecision(8) << x << ' ' << y << '\n';
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