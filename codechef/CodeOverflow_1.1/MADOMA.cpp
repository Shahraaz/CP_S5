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

typedef vector<ll> row;

struct matrix
{
    vector<row> MAT;
    matrix() {}
    matrix(ll n, ll m)
    {
        MAT.resize(n, row(m));
    }
};

matrix mul(matrix &A, matrix &B)
{
    int n = A.MAT.size(), m = B.MAT.size(), k = B.MAT[0].size();
    matrix X(n, k);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < k; ++j)
        {
            X.MAT[i][j] = 0;
            for (int k = 0; k < m; ++k)
                X.MAT[i][j] = (X.MAT[i][j] + A.MAT[i][k] * B.MAT[k][j]) % MOD;
        }
    return X;
}

matrix unit(int n)
{
    matrix X(n, n);
    for (int i = 0; i < n; ++i)
        X.MAT[i][i] = 1;
    return X;
}

matrix POWER(matrix &A, ll index)
{
    db("POWER", index);
    matrix temp;
    if (index == 0)
        return unit(A.MAT.size());
    temp = POWER(A, index / 2);
    temp = mul(temp, temp);
    if (index & 1)
        return mul(temp, A);
    return temp;
}

void solveCase(int caseNo)
{
    int n;
    ll a, b;
    cin >> n >> a >> b;
    if (n == 1)
        cout << a << '\n';
    else if (n == 2)
        cout << b << '\n';
    else
    {
        matrix m(2, 2);
        m.MAT[0][0] = 3;
        m.MAT[0][1] = 4;
        m.MAT[1][0] = 1;
        m.MAT[1][1] = 0;
        m = POWER(m, n - 2);
        cout << (m.MAT[0][0] * b + m.MAT[0][1] * a) % MOD << '\n';
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
