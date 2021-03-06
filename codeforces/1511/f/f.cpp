#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 998244353;

const int kmod = MOD;

int mul(int a, int b, int mod = kmod)
{
    return (long long)a * b % mod;
}

int add(int a, int b, int mod = kmod)
{
    a += b;
    if (a >= mod)
        a -= mod;
    return a;
}

int sub(int a, int b, int mod = kmod)
{
    a -= b;
    if (a < 0)
        a += mod;
    return a;
}

int power(int base, int index, int mod = kmod)
{
    if (index == 0)
        return 1;
    int temp = power(base, index / 2, mod);
    temp = mul(temp, temp, mod);
    if (index & 1)
        temp = mul(temp, base, mod);
    return temp;
}

int mod_inv(int x, int mod = kmod)
{
    return power(x, mod - 2, mod);
}

// const int _n = 2e5 + 10;
// vector<int> Fact(_n), Inv(_n);

// void pre()
// {
//     Fact[0] = 1;
//     for (int i = 1; i < _n; ++i)
//         Fact[i] = mul(Fact[i - 1], i);
//     Inv[_n - 1] = mod_inv(Fact[_n - 1]);
//     for (int i = _n - 2; i >= 0; --i)
//         Inv[i] = mul(Inv[i + 1], (1 + i));
// }

// int ncr(int n, int r)
// {
//     if (n < 0 || r < 0 || n - r < 0)
//         return 0;
//     return mul(Fact[n], mul(Inv[r], Inv[n - r]));
// }

// int npr(int n, int r)
// {
//     if (n < 0 || r < 0 || n - r < 0)
//         return 0;
//     return mul(Fact[n], Inv[n - r]);
// }

struct matrix
{
    vector<vector<long long>> MAT;
    matrix() {}
    matrix(long long n, long long m)
    {
        MAT.resize(n, vector<long long>(m));
    }
};

matrix mul(const matrix &A, const matrix &B)
{
    int n = A.MAT.size(), m = B.MAT.size(), k = B.MAT[0].size();
    matrix X(n, k);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < k; ++j)
        {
            X.MAT[i][j] = 0;
            for (int k = 0; k < m; ++k)
                X.MAT[i][j] = add(X.MAT[i][j], mul(A.MAT[i][k], B.MAT[k][j]));
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

matrix power(const matrix &A, long long index)
{
    matrix temp;
    if (index == 0)
        return unit(A.MAT.size());
    temp = power(A, index / 2);
    temp = mul(temp, temp);
    if (index & 1)
        return mul(temp, A);
    return temp;
}

const int AL = 26;

struct node
{
    int nxt[AL];
    bool term;
    node()
    {
        memset(nxt, -1, sizeof(nxt));
        term = false;
    };
    int &operator[](const int x)
    {
        return nxt[x];
    }
};

vector<node> trie = vector<node>(1, node());

void add(const string &s)
{
    int cur = 0;
    int d = 1;
    for (const char &c : s)
    {
        ++d;
        if (trie[cur][c - 'a'] == -1)
        {
            trie[cur][c - 'a'] = trie.size();
            trie.push_back(node());
        }
        cur = trie[cur][c - 'a'];
    }
    trie[cur].term = true;
}

map<pair<int, int>, int> num;
queue<pair<int, int>> q;

int get(int u, int v)
{
    if (u > v)
        swap(u, v);
    if (num.find({u, v}) == num.end())
    {
        int k = num.size();
        num[{u, v}] = k;
        q.push({u, v});
    }
    return num[{u, v}];
}

void solveCase()
{
    int n, m;
    cin >> n >> m;
    for (size_t i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        add(s);
    }
    q.push({0, 0});
    num[{0, 0}] = 0;
    matrix init(120, 120);
    while (!q.empty())
    {
        auto top = q.front();
        q.pop();
        int x = num[top];
        db(top, x);
        for (int i = 0; i < AL; i++)
        {
            int tov = trie[top.first][i];
            int tou = trie[top.second][i];
            if (tov == -1 || tou == -1)
                continue;
            init.MAT[x][get(tov, tou)]++;
            if (trie[tov].term)
                init.MAT[x][get(0, tou)]++;
            if (trie[tou].term)
                init.MAT[x][get(tov, 0)]++;
            if (trie[tov].term && trie[tou].term)
                init.MAT[x][get(0, 0)]++;
        }
    }
    init = power(init, m);
    cout << init.MAT[0][0] << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}