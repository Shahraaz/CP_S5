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
const int NAX = 4e5 + 5, MOD = 1000000007;

int mapper[NAX * 2];
int invmapper[NAX * 2];
int k, fptr;
string str;
ll ways[NAX * 2];
vector<pair<int, int>> nodes;

void build(int node, int lvl)
{
    if (lvl != k)
    {
        build(2 * node, lvl + 1);
        build(2 * node + 1, lvl + 1);
        // if (str[fptr] == '0')
        //     ways[node] = ways[2 * node];
        // else if (str[fptr] == '1')
        //     ways[node] = ways[2 * node + 1];
        // else
        //     ways[node] = ways[2 * node] + ways[2 * node + 1];
        // mapper[fptr] = node;
        // db(fptr, node, ways[node]);
        // ++fptr;
    }
    nodes.pb({-lvl, node});
    // else
    //     ways[node] = 1;
}

ll calc(int p, char c)
{
    ll res = 0;
    int node = invmapper[p];
    str[p] = c;
    while (node)
    {
        res = 0;
        if (str[mapper[node]] == '0')
        {
            res += ways[node * 2];
        }
        else if (str[mapper[node]] == '1')
        {
            res += ways[node * 2 + 1];
        }
        else
        {
            res += ways[node * 2];
            res += ways[node * 2 + 1];
        }
        ways[node] = res;
        node /= 2;
    }
    // str[p] = bak;
    return res;
}

void solveCase()
{
    cin >> k;
    cin >> str;
    build(1, 0);
    sort(all(nodes));
    db(nodes);
    for (auto &n : nodes)
    {
        if (n.first == -k)
        {
            ways[n.second] = 1;
            continue;
        }
        if (str[fptr] == '0')
            ways[n.second] += ways[n.second * 2];
        else if (str[fptr] == '1')
            ways[n.second] += ways[n.second * 2 + 1];
        else
        {
            ways[n.second] += ways[n.second * 2 + 1];
            ways[n.second] += ways[n.second * 2];
        }
        invmapper[fptr] = n.second;
        mapper[n.second] = fptr++;
        db(n, mapper[n.second], ways[n.second]);
    }
    int q;
    cin >> q;
    for (size_t i = 0; i < q; i++)
    {
        int p;
        cin >> p;
        --p;
        char c;
        cin >> c;
        cout << calc(p, c) << '\n';
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