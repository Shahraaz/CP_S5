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
    ll a, b;
    cin >> a >> b;
    string str;
    cin >> str;
    int n = str.size();
    vector<int> nextMine(n + 1, MOD);
    priority_queue<ll, vector<ll>, greater<ll>> Q;
    ll res = 0;
    for (int i = n - 1; i >= 0; i--)
        if (str[i] == '0')
            nextMine[i] = nextMine[i + 1];
        else
        {
            nextMine[i] = i;
            if (nextMine[i + 1] != (i + 1))
            {
                db(i, nextMine[i + 1]);
                res += a;
                if (nextMine[i + 1] != MOD)
                    Q.push(nextMine[i + 1] - i - 1);
            }
        }
    while (Q.size() && Q.top() * b < a)
    {
        db(Q.top());
        res -= a;
        res += Q.top() * b;
        Q.pop();
    }
    cout << res << '\n';
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
