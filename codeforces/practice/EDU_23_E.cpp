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

const int LIM = 27;
int left_ptr[(LIM + 1) * NAX], right_ptr[(LIM + 1) * NAX];
int cnt[(LIM + 1) * NAX];
const int root = 0;
int sz = 1;

int get_new_node()
{
    return sz++;
}

void add(int num)
{
    int curr = root;
    for (int i = LIM; i >= 0; i--)
    {
        cnt[curr]++;
        if (num & (1 << i))
        {
            if (right_ptr[curr] == -1)
                right_ptr[curr] = get_new_node();
            curr = right_ptr[curr];
        }
        else
        {
            if (left_ptr[curr] == -1)
                left_ptr[curr] = get_new_node();
            curr = left_ptr[curr];
        }
    }
    cnt[curr]++;
}

void remove(int num)
{
    int curr = root;
    for (int i = LIM; i >= 0; i--)
    {
        cnt[curr]--;
        if (num & (1 << i))
        {
            if (right_ptr[curr] == -1)
                break;
            curr = right_ptr[curr];
        }
        else
        {
            if (left_ptr[curr] == -1)
                break;
            curr = left_ptr[curr];
        }
    }
    cnt[curr]--;
}

int query(int p, int l)
{
    int res = 0;
    int curr = root;
    for (int i = LIM; i >= 0; i--)
    {
        int pj = p & (1 << i);
        pj = pj > 0;
        int lj = l & (1 << i);
        lj = lj > 0;
        db(curr, pj, lj, left_ptr[curr], right_ptr[curr]);
        if (pj == 0 && lj == 0)
        {
            if (left_ptr[curr] == -1)
                break;
            curr = left_ptr[curr];
        }
        else if (pj == 0 && lj == 1)
        {
            if (left_ptr[curr] != -1)
                res += cnt[left_ptr[curr]];
            if (right_ptr[curr] == -1)
                break;
            curr = right_ptr[curr];
        }
        else if (pj == 1 && lj == 0)
        {
            if (right_ptr[curr] == -1)
                break;
            curr = right_ptr[curr];
        }
        else if (pj == 1 && lj == 1)
        {
            if (right_ptr[curr] != -1)
                res += cnt[right_ptr[curr]];
            if (left_ptr[curr] == -1)
                break;
            curr = left_ptr[curr];
        }
    }
    return res;
}

void print()
{
#ifdef LOCAL
    queue<int> Q;
    Q.push(root);
    while (Q.size())
    {
        auto top = Q.front();
        Q.pop();
        db(top, cnt[top], left_ptr[top], right_ptr[top]);
        if (left_ptr[top] != -1)
            Q.push(left_ptr[top]);
        if (right_ptr[top] != -1)
            Q.push(right_ptr[top]);
    }

#endif
}

void solveCase()
{
    int q;
    cin >> q;
    memset(left_ptr, -1, sizeof left_ptr);
    memset(right_ptr, -1, sizeof right_ptr);
    for (size_t i = 0; i < q; i++)
    {
        int ch, p;
        cin >> ch >> p;
        print();
        db(ch, p);
        if (ch == 1)
            add(p);
        else if (ch == 2)
            remove(p);
        else
        {
            int l;
            cin >> l;
            db(l);
            cout << query(p, l) << '\n';
        }
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
