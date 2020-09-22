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

const int NAX = 1e5 + 5, MOD = 1000000007;

vector<int> poses[NAX];
int a[NAX];
vector<int> stree[4 * NAX];

void build(int node, int left, int right)
{
    if (left > right)
        return;
    if (left == right)
    {
        stree[node].pb(a[left]);
        return;
    }
    int mid = (left + right) / 2;
    build(node * 2, left, mid);
    build(node * 2 + 1, mid + 1, right);
    merge(stree[2 * node].begin(), stree[2 * node].end(), stree[2 * node + 1].begin(), stree[2 * node + 1].end(), back_inserter(stree[node]));
}

int query(int node, int left, int right, int qstart, int qend, int k)
{
    if (qend < left || right < qstart || left > right)
        return 0;
    if (qstart <= left && right <= qend)
    {
        db(node, left, right, qstart, qend, k);
        db(stree[node]);
        return upper_bound(all(stree[node]), k) - stree[node].begin();
    }
    int mid = (left + right) / 2;
    return query(node * 2, left, mid, qstart, qend, k) + query(node * 2 + 1, mid + 1, right, qstart, qend, k);
}

void solveCase()
{
    int n, k;
    cin >> n >> k;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        poses[a[i]].pb(i);
    }
    for (size_t i = 1; i < NAX; i++)
    {
        if (poses[i].empty())
            continue;
        db(i, poses[i]);
        for (int j = 0; j < poses[i].size(); j++)
        {
            a[poses[i][j]] = (j - k >= 0) ? poses[i][j - k] : -2;
            db(j - k, a[poses[i][j]]);
        }
    }
#ifdef LOCAL
    for (size_t i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << '\n';
#endif
    build(1, 0, n - 1);
    int last = 0;
    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        // --l, --r;
        l = (l + last) % n;
        r = (r + last) % n;
        if (l > r)
            swap(l, r);
        last = query(1, 0, n - 1, l, r, l - 1);
        cout << last << '\n';
    }
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
