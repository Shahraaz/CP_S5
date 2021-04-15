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
    string a, b;
    cin >> a >> b;
    vector<int> v(n);
    for (size_t i = 0; i < n; i++)
    {
        v[i] = a[i] == '0' ? -1 : 1;
        if (i > 0)
            v[i] += v[i - 1];
    }
    bool states = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        char a_i = a[i];
        if (states)
            a_i = '1' ^ '0' ^ a_i;
        db(i, a[i], b[i], states, a_i);
        if (a_i != b[i])
        {
            if (v[i] == 0)
                states = !states;
            else
            {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
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
        solveCase();
    return 0;
}