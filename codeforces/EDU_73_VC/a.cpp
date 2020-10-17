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
    map<ll, int> vecc;
    for (size_t i = 0; i < n; i++)
    {
        ll x;
        cin >> x;
        if (x <= 2048)
            vecc[x]++;
    }
    // sort(all(vecc));
    while (vecc.size())
    {
        auto it = *vecc.begin();
        db(it);
        db(vecc);
        vecc.erase(it.f);
        if (it.f == 2048)
        {
            cout << "YES\n";
            return;
        }
        else if (it.f > 2048)
        {
            break;
        }
        if (it.s > 1)
            vecc[it.f * 2] += it.s / 2;
    }
    cout << "NO\n";
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
