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
    int n;
    cin >> n;
    pair<int, int> a, b;
    cin >> a.first >> a.second;
    cin >> b.first >> b.second;
    --a.first, --a.second;
    --b.first, --b.second;
    vector<pair<int, int>> moves;
    set<pair<int, int>> moves_set;
    for (size_t i = 0; i < n; i++)
    {
        int dx, dy;
        cin >> dx >> dy;
        moves.pb({dx, dy});
        moves_set.insert({dx, dy});
    }
    auto isvalid = [&](pair<int, int> node) -> bool
    {
        return 0 <= node.first & node.first < n && 0 <= node.second && node.second < n;
    };
    auto can_reach = [&](pair<int, int> src, pair<int, int> dest) -> bool
    {
        if (src == dest)
            return true;
        for (size_t i = 0; i < n; i++)
        {
            pair<int, int> next;
            next.first = src.first + moves[i].first;
            next.second = src.second + moves[i].second;
            if (isvalid(next))
            {
                pair<int, int> nnext;
                nnext.first = dest.first - next.first;
                nnext.second = dest.second - next.second;
                if (moves_set.find(nnext) != moves_set.end())
                    return true;
            }
        }
        return false;
    };
    if (can_reach(a, b))
    {
        cout << "Alice wins\n";
        return;
    }
    if (n < 500)
    {
        set<pair<int, int>> vis;
        queue<pair<pair<int, int>, int>> Q;
        Q.push({b, 0});
        vis.insert(b);
        while (Q.size())
        {
            auto top = Q.front();
            Q.pop();
            if (top.second == 2)
                continue;
            for (size_t i = 0; i < n; i++)
            {
                pair<int, int> next;
                next.first = top.first.first + moves[i].first;
                next.second = top.first.second + moves[i].second;
                if (isvalid(next) && vis.find(next) == vis.end())
                {
                    vis.insert(next);
                    Q.push({next, top.second + 1});
                }
            }
        }
        if (vis.size() == n * n)
        {
            cout << "Bob wins\n";
            return;
        }
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < n; j++)
                if (vis.find({i, j}) == vis.end())
                {
                    cout << "tie " << i + 1 << ' ' << j + 1 << '\n';
                    return;
                }
        assert(false);
    }
    for (size_t i = 0; i < 500; i++)
    {
        int x = rand() % n;
        int y = rand() % n;
        if (can_reach(b, {x, y}))
            continue;
        cout << "tie " << x + 1 << ' ' << y + 1 << '\n';
        return;
    }
    assert(false);
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