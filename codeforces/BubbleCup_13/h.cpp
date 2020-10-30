// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 5e5 + 5, MOD = 1000000007;

int n, q, k;
int x[NAX], y[NAX];
int _type[NAX], qidx[NAX];
vector<int> z;
vector<pair<int, int>> stree[4 * NAX];

void update(int node, int sl, int sr, int l, int r, pair<int, int> p)
{
    db(node, sl, sr, l, r, p);
    if (r < sl || sr < l)
        return;
    if (l <= sl && sr <= r)
    {
        stree[node].pb(p);
        return;
    }
    int mid = sl + sr;
    mid /= 2;
    update(2 * node, sl, mid, l, r, p);
    update(2 * node + 1, mid + 1, sr, l, r, p);
}

struct reversibleDSU
{
    int n, compCnt;
    vector<int> par, sz;
    vector<pair<int, int>> st;
    reversibleDSU(int _n)
    {
        compCnt = n = _n;
        sz.assign(n, 1);
        par.resize(n);
        iota(all(par), 0);
    }

    int root(int x)
    {
        while (x != par[x])
            x = par[x];
        return x;
    }

    int getVersion()
    {
        return st.size();
    }

    void roolback(int targ)
    {
        assert(targ <= st.size());
        while (st.size() > targ)
        {
            auto x = st.back().f;
            auto y = st.back().s;
            st.pop_back();
            ++compCnt;
            sz[x] -= sz[y];
            par[y] = y;
        }
    }

    bool merge(int x, int y)
    {
        x = root(x), y = root(y);
        if (x != y)
        {
            if (sz[y] > sz[x])
                swap(x, y);
            sz[x] += sz[y];
            par[y] = x;
            --compCnt;
            st.pb({x, y});
            return true;
        }
        return false;
    }
};

reversibleDSU D(0);

void dfs(int node, int l, int r)
{
    if (l > r)
        return;
    db(l, r, node);
    db(stree[node]);
    auto ver = D.getVersion();
    for (auto &x : stree[node])
        D.merge(x.f, x.s);
    if (l == r)
    {
        db(z[l]);
        cout << D.sz[D.root(z[l])] << '\n';
        D.roolback(ver);
        return;
    }
    int mid = l + r;
    mid /= 2;
    dfs(2 * node, l, mid);
    dfs(2 * node + 1, mid + 1, r);
    D.roolback(ver);
}

void solveCase()
{
    cin >> n >> q >> k;
    int todayIdx = 0;
    int nq = 0;
    for (size_t i = 0; i < q; i++)
    {
        cin >> _type[i];
        if (_type[i] == 1)
            cin >> x[i] >> y[i];
        else if (_type[i] == 2)
        {
            qidx[i] = nq;
            nq++;
            int cz;
            cin >> cz;
            z.pb(cz);
        }
        else
            todayIdx++;
    }
    db("inp");
    deque<pair<int, int>> qry;
    for (int i = q - 1; i >= 0; i--)
    {
        if (_type[i] == 3)
            --todayIdx;
        else if (_type[i] == 2)
        {
            qry.push_front({todayIdx, qidx[i]});
        }
        else
        {
            while (qry.size() && qry.back().f >= todayIdx + k)
                qry.pop_back();
            db(i, _type[i], todayIdx, qidx[i], x[i], y[i]);
            db(qry);
            if (qry.size())
                update(1, 0, nq - 1, qry.front().s, qry.back().s, {x[i], y[i]});
        }
    }
    D = reversibleDSU(n + 1);
    db("phase 2");
    dfs(1, 0, nq - 1);
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
