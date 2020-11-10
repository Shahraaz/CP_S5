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

const int NAX = 2e5 + 5, MOD = 1000000007;

struct aho_corasick
{
    struct node
    {
        map<int, int> nxt, go;
        int p, pch;
        int suf, ssuf;
        multiset<int> vals;
        bool term = false;
        node()
        {
            p = pch = suf = ssuf = -1;
            term = false;
        }
    };

    vector<node> nodes;

    aho_corasick() { nodes.resize(1); }

    int add(const string &s)
    {
        int v = 0;
        db("add", s);
        for (auto &curr : s)
        {
            int c = curr - 'a';
            if (nodes[v].nxt.find(c) == nodes[v].nxt.end())
            {
                nodes[v].nxt[c] = nodes.size();
                nodes.emplace_back(node());
                nodes.back().p = v;
                nodes.back().pch = c;
            }
            v = nodes[v].nxt[c];
            db(v, curr);
        }
        nodes[v].term = true;
        nodes[v].vals.insert(0);
        db(nodes[v].term, nodes[v].vals);
        return v;
    }

    int feed(const string &s)
    {
        db(s);
        int v = 0, ans = -1;
        for (auto &curr : s)
        {
            int c = curr - 'a';
            db(curr, v);
            v = go(v, c);
            int u = v;
            while (u != 0)
            {
                db(u);
                if (nodes[u].vals.size())
                    ans = max(ans, *nodes[u].vals.rbegin());
                u = ssuf(u);
            }
        }
        return ans;
    }

    int go(int v, int c)
    {
        if (nodes[v].go.find(c) != nodes[v].go.end())
            return nodes[v].go[c];
        if (nodes[v].nxt.find(c) != nodes[v].nxt.end())
            return nodes[v].go[c] = nodes[v].nxt[c];
        if (v == 0)
            return nodes[v].go[c] = 0;
        return nodes[v].go[c] = go(suf(v), c);
    }

    int suf(int v)
    {
        if (nodes[v].suf != -1)
            return nodes[v].suf;
        if (v == 0 || nodes[v].p == 0)
            return nodes[v].suf = 0;
        return nodes[v].suf = go(suf(nodes[v].p), nodes[v].pch);
    }

    int ssuf(int v)
    {
        if (nodes[v].ssuf != -1)
            return nodes[v].ssuf;
        if (v == 0 || nodes[v].p == 0)
            return nodes[v].ssuf = 0;
        int s = suf(v);
        if (nodes[s].term)
            return nodes[v].ssuf = s;
        return nodes[v].ssuf = ssuf(s);
    }
};

vector<int> val, pos;

void solveCase()
{
    aho_corasick ac;
    int n, m;
    cin >> n >> m;
    val.resize(n);
    pos.resize(n);
    for (size_t i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        pos[i] = ac.add(str);
    }
    for (size_t i = 0; i < m; i++)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int j, x;
            cin >> j >> x;
            --j;
            ac.nodes[pos[j]].vals.erase(ac.nodes[pos[j]].vals.find(val[j]));
            val[j] = x;
            ac.nodes[pos[j]].vals.insert(val[j]);
        }
        else
        {
            string q;
            cin >> q;
            cout << ac.feed(q) << '\n';
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
