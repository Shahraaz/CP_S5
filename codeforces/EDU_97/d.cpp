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

void solveCase()
{
    int n;
    cin >> n;
    deque<int> order(n);
    for (auto &x : order)
        cin >> x;
    queue<pair<int, int>> Q;
    Q.push({1, 0});
    order.pop_front();
    int maxDepth = 0;
    while (Q.size())
    {
        auto top = Q.front();
        int node = top.f;
        maxDepth = max(maxDepth, top.s);
        Q.pop();
        maxDepth = max(maxDepth, top.s);
        int prev = 0;
        while (order.size() && prev <= order.front())
        {
            prev = order.front();
            Q.push({order.front(), top.s + 1});
            order.pop_front();
        }
    }
    cout << maxDepth << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
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
