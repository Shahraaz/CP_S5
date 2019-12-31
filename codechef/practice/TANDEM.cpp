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

const int NAX = 211111 + 5, MOD = 1000000007;

char t[NAX];
int n, sa[NAX], sai[NAX << 1], lcp[NAX], sai1[NAX << 1], lcp1[NAX];
ll key[NAX];

bool comp(int i, int j)
{
    return key[i] < key[j];
}

void fill_sai()
{
    sort(sa, sa + n, comp);
    sai[sa[0]] = 0;
    for (int i = 1; i < n; ++i)
        sai[sa[i]] = key[sa[i]] == key[sa[i - 1]] ? sai[sa[i - 1]] : i;
}

void get_suffix_array()
{
    db("Stage 1");
    for (int i = 0; i < n; ++i)
    {
        sa[i] = i;
        sai[i] = sai[i + n] = -1;
        key[i] = t[i];
    }
    db("Stage 2");
    fill_sai();
    db("Stage 3");
    for (int p = 1; p <= n; p <<= 1)
    {
        for (int i = 0; i < n; ++i)
            key[i] = sai[i] * (n + 1LL) + sai[i + p];
        fill_sai();
    }
    db("Stage 4");
}

void get_lcp()
{
    db("Stage a");
    int l = 0;
    for (int i = 0; i < n; ++i)
        lcp[i] = 0;
    db("Stage b");
    for (int i = 0; i < n - 1; ++i)
    {
        int k = sai[i];
        int j = sai[k - 1];
        while (t[i + l] == t[j + l])
            ++l;
        lcp[k] = l;
        if (l > 0)
            --l;
    }
    db("Stage c");
}

int w[NAX], lg;

void init_w()
{
    for (lg = 0; 1 << lg <= n; ++lg)
        w[1 << lg] = lg;
    for (int i = 1; i < n; ++i)
        if (w[i] == 0)
            w[i] = w[i - 1];
}

struct ST
{
    int **m;
    ST(int *a, int n)
    {
        m = new int *[lg];
        m[0] = a;
        for (int v = 1; v < lg; ++v)
        {
            m[v] = new int[n];
            for (int i = 0; i < n; ++i)
            {
                int j = i + 1 << (v - 1);
                if (j < n)
                    m[v][i] = min(m[v - 1][i], m[v - 1][j]);
                else
                    m[v][i] = m[v - 1][i];
            }
        }
    }
    int gmin(int i, int j)
    {
        int v = w[j - i];
        return min(m[v][i], m[v][j - (1 << v)]);
    }
};

ST *t1, *t2;

void init()
{
    t[n++] = '$';
    db("a");
    get_suffix_array();
    db("b");
    get_lcp();
    db("c");
    for (int i = 0; i < n; ++i)
        lcp1[i] = lcp[i], sai1[i] = sai[i];
    db("d");
    for (int i = 0, j = n - 2; i < j; ++i, --j)
        swap(t[i], t[j]);
    db("e");
    get_suffix_array();
    db("f");
    get_lcp();
    db("g");
    --n;
    init_w();
    db("h");
    t1 = new ST(lcp1 + 1, n);
    db("i");
    t2 = new ST(lcp + 1, n);
    db("j");
}

int _lcp(int *sai, ST *t, int i, int j, int k)
{
    i = sai[i];
    j = sai[j];
    k = sai[k];
    int I = min({i, j, k});
    int J = max({i, j, k});
    return t->gmin(I, J);
}

int get_lcp(int i, int j, int k, int l)
{
    return min(l, _lcp(sai1, t1, i, j, k));
}

int get_lcs(int i, int j, int k, int l)
{
    return min(l, _lcp(sai, t2, n - 1 - i, n - 1 - j, n - 1 - k));
}

void solveCase(int caseNo)
{
    cin >> t;
    n = strlen(t);
    db("here");
    init();
    db("here2");
    ll intresting, boring;
    intresting = boring = 0;
    for (int l = 1; l <= n / 3; ++l)
        for (int i = 0; i < n - 2 * l; i += l)
        {
            int j = i + l;
            int k = j + l;
            int right = get_lcp(i, j, k, l + 1);
            int left = get_lcs(i, j, k, l);
            int total = min(right, l) + left - 1;
            if (total >= l)
            {
                if (right > l)
                    boring += total - l + 1;
                else
                    boring += total - l, intresting = intresting + 1;
            }
        }
    cout << intresting << ' ' << boring << '\n';
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
