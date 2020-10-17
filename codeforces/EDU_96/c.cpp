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
    cout << 2 << '\n';
    priority_queue<int> Q;
    for (size_t i = 0; i < n; i++)
        Q.push(i + 1);
    while (Q.size() > 1)
    {
        auto top1 = Q.top();
        Q.pop();
        auto top2 = Q.top();
        Q.pop();
        cout << top1 << ' ' << top2 << '\n';
        Q.push((top1 + top2 + 1) / 2);
    }
    assert(Q.top() == 2);
    // cout << Q.top() << '\n';
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
