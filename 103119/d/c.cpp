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
const int NAX = 2e5 + 5, MOD = 1000000007;

const int AL = 2;

struct node
{
    int nxt[AL];
    int cnt;
    vector<int> a;
    node()
    {
        memset(nxt, -1, sizeof(nxt));
        cnt = 0;
    };
    int &operator[](const int x)
    {
        return nxt[x];
    }
};

vector<node> trie = vector<node>(1, node());

void add(int &s)
{
    int cur = 0;
    int d = 1;
    for (int i = 32 - 1; i >= 0; i--)
    {
        int c = (s >> i) & 1;
        if (trie[cur][c] == -1)
        {
            trie[cur][c] = trie.size();
            trie.push_back(node());
        }
        trie[cur].cnt += 1;
        trie[cur].a.pb(s);
        cur = trie[cur][c];
    }
    trie[cur].cnt += 1;
    trie[cur].a.pb(s);
}

void solveCase()
{
    trie = vector<node>(1, node());
    int n = 10;
    cin >> n;
    vector<int> a(n);
    map<int, vector<int>> poses;
    for (size_t i = 0; i < n; i++)
    {
        auto &x = a[i];
        x = rand() % 16;
        cin >> x;
        add(x);
        poses[x].pb(i);
    }
    vector<int> level, res(n);
    level = {0}; // root
    int globres = 0;
    for (int i = 32 - 1; i >= 0; i--)
    {
        vector<int> next;
        bool ok = true;
        for (auto &no : level)
        {
            vector<int> sizes;
            for (size_t j = 0; j < 2; j++)
            {
                auto x = trie[no].nxt[j];
                if (x == -1)
                {
                    sizes.pb(0);
                    continue;
                }
                next.pb(x);
                sizes.pb(trie[x].cnt);
            }
            sort(all(sizes));
            ok = ok && sizes[1] <= 2;
        }
        db(i, ok, level, next);
        if (ok)
        {
            globres = MOD;
            for (auto &no : level)
            {
                vector<int> now;
                for (auto &c : trie[no].nxt)
                {
                    if (c == -1)
                        continue;
                    for (auto &x : trie[c].a)
                        now.pb(x);
                }
                int tempres = 0;
                int best = 0;
                db(no, now);
                for (size_t i = 0; i < (1 << now.size()); i++)
                {
                    vector<int> one, two;
                    for (size_t j = 0; j < now.size(); j++)
                    {
                        if ((i >> j) & 1)
                            one.pb(now[j]);
                        else
                            two.pb(now[j]);
                    }
                    int res = MOD;
                    for (size_t i = 0; i < one.size(); i++)
                        for (size_t j = i + 1; j < one.size(); j++)
                            res = min(res, one[i] ^ one[j]);
                    for (size_t i = 0; i < two.size(); i++)
                        for (size_t j = i + 1; j < two.size(); j++)
                            res = min(res, two[i] ^ two[j]);
                    if (tempres < res)
                    {
                        tempres = res;
                        best = i;
                    }
                }
                for (size_t j = 0; j < now.size(); j++)
                {
                    int idx = poses[now[j]].back();
                    poses[now[j]].pop_back();
                    res[idx] = (best >> j) & 1;
                }
                globres = min(globres, tempres);
            }
            break;
        }
        level = next;
    }
    cout << globres << '\n';
    for (auto &x : res)
        cout << x + 1;
    cout << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    srand(time(NULL));
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}