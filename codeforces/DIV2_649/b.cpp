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
    vector<int> vecc(n);
    for (auto &x : vecc)
        cin >> x;
    deque<int> Q;
    for (int i = n - 1; i >= 0; i--)
    {
        if (Q.size() <= 1)
            Q.push_front(vecc[i]);
        else if (vecc[i] <= Q[0] && Q[0] <= Q[1])
        {
            Q.pop_front();
            Q.push_front(vecc[i]);
        }
        else if (vecc[i] >= Q[0] && Q[0] >= Q[1])
        {
            Q.pop_front();
            Q.push_front(vecc[i]);
        }
        else
            Q.push_front(vecc[i]);
    }
    db(Q);
    cout << Q.size() << '\n';
    for (auto &x : Q)
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
    cin >> t;
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