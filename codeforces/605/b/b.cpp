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

void solveCase()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, pair<int, int>>> edges(m);
    vector<pair<int, int>> res(m);
    for (size_t i = 0; i < m; i++)
    {
        auto &x = edges[i];
        cin >> x.first >> x.second.first;
        x.second.first = 1 - x.second.first;
        x.second.second = i;
    }

    sort(all(edges));

    set<int> used, unused;
    set<pair<int, int>> degree_node;
    for (size_t i = 0; i < n; i++)
        unused.insert(i);

    auto get_unused_node = [&]() -> int {
        if (unused.empty())
        {
            cout << -1 << '\n';
            exit(0);
        }
        auto node = *unused.begin();
        unused.erase(node);
        return node;
    };

    vector<int> degree(n);
    vector<int> used_nodes;
    int ptr = 0;

    auto alter_degree = [&](int node) -> void {
        if (degree[node])
        {
            auto it = degree_node.find({degree[node], node});
            assert(it != degree_node.end());
            degree_node.erase(it);
        }
        else
            used_nodes.pb(node);
        degree[node]++;
        degree_node.insert({degree[node], node});
    };

    set<pair<int, int>> unused_pairs;

    for (auto &x : edges)
    {
        db(x);
        db(degree_node);
        db(unused);
        db(unused_pairs);
        if (x.second.first == 0)
        {
            if (degree_node.empty())
            {
                auto a = get_unused_node();
                auto b = get_unused_node();
                res[x.second.second] = {a, b};
                alter_degree(a);
                alter_degree(b);
            }
            else
            {
                auto a = get_unused_node();
                auto b = used_nodes[0];
                res[x.second.second] = {a, b};
                if (unused_pairs.size() < m)
                    for (auto &v : used_nodes)
                        if (v != a && v != b)
                            unused_pairs.insert({a, v});
                alter_degree(a);
                alter_degree(b);
            }
        }
        else
        {
            if (unused_pairs.empty())
            {
                cout << -1 << '\n';
                exit(0);
            }
            auto a = unused_pairs.begin()->first;
            auto b = unused_pairs.begin()->second;
            unused_pairs.erase(unused_pairs.begin());
            res[x.second.second] = {a, b};
            alter_degree(a);
            alter_degree(b);
        }
    }
    for (auto &x : res)
    {
        cout << x.first + 1 << ' ' << x.second + 1 << '\n';
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