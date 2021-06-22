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
const int NAX = 1e5 + 5, MOD = 1000000007;
const int PNAX = 1e6 + 5;

struct node
{
    int count;
    node *left, *right;

    node(int _count, node *_left, node *_right) : count(_count), left(_left), right(_right) {}
    node *insert(int l, int r, int w, int dx);
};

node *null = new node(0, NULL, NULL);

node *node::insert(int l, int r, int w, int dx)
{
    if (l <= w && w <= r)
    {
        if (l == r)
            return new node(this->count + dx, null, null);

        int mid = (l + r) / 2;

        return new node(this->count + dx, this->left->insert(l, mid, w, dx), this->right->insert(mid + 1, r, w, dx));
    }
    return this;
}

int query(node *a, node *b, int start, int end, int qstart, int qend)
{
    if (qend < start || qstart > end || start > end)
        return 0;
    if (qstart <= start && end <= qend)
    {
        // db(start, end, qstart, qend, a->count - b->count);
        return a->count - b->count;
    }
    int m = (start + end) / 2;
    int ret = query(a->left, b->left, start, m, qstart, qend) + query(a->right, b->right, m + 1, end, qstart, qend);
    // db(start, end, qstart, qend, ret);
    return ret;
}

// const int LIM = 1e5 + 5;
node *root[PNAX];
int is_composite[PNAX];
// null->left = null->right = null;

int a[NAX];
vector<int> poses[PNAX];

void solveCase()
{
    int n, q;
    n = 1e5;
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        a[i] = rand() % PNAX + 1;
        cin >> a[i];
        poses[a[i]].pb(i);
        // db(i, a[i]);
    }
    null->left = null->right = null;
    node *curr_root = null;
    is_composite[0] = is_composite[1] = true;
    for (size_t i = 0; i < PNAX; i++)
    {
        if (is_composite[i] == 0)
        {
            for (size_t j = i; j < PNAX; j += i)
            {
                is_composite[j] = 1;
                if (poses[j].empty())
                    continue;
                int j1 = j;
                int cnt = 0;
                while (j1 % i == 0)
                    j1 /= i, ++cnt;
                for (auto &idx : poses[j])
                {
                    curr_root = curr_root->insert(0, n - 1, idx, cnt);
                }
            }
        }
        root[i] = curr_root;
    }
    q = 1e5;
    cin >> q;
    for (size_t i = 0; i < q; i++)
    {
        int l = 1 + rand() % NAX, r = 1 + rand() % NAX, x = 1 + rand() % PNAX, y = 1 + rand() % PNAX;
        if (l > r)
            swap(l, r);
        if (x > y)
            swap(x, y);
        cin >> l >> r >> x >> y;
        --l, --r;
        // db(l, r, x, y);
        cout << query(root[y], root[x - 1], 0, n - 1, l, r) << '\n';
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
        solveCase();
    return 0;
}