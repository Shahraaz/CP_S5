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
    vector<int> a(n);
    vector<int> res(n, NAX);
    for (auto &x : a)
        cin >> x;
    set<int> vis;
    queue<int> emptylocs;
    if (a[0] == 1)
    {
        vis.insert(0);
        res[0] = 0;
    }
    else
        emptylocs.push(0);
    for (size_t i = 1; i < n; i++)
    {
        if (a[i] == a[i - 1])
        {
            emptylocs.push(i);
            continue;
        }
        res[i] = a[i - 1];
        int low = a[i - 1] + 1, high = a[i] - 1;
        while (low <= high)
        {
            if (vis.count(low) == 0)
            {
                if (emptylocs.empty())
                {
                    cout << -1 << '\n';
                    return;
                }
                res[emptylocs.front()] = low;
                emptylocs.pop();
            }
            ++low;
        }
    }
    for (auto &x : res)
    {
        cout << x << ' ';
    }
    cout << '\n';
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
#ifdef TIMER
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}