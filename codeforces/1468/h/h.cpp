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

#define int ll

void solveCase()
{
    int n, m, k;
    cin >> n >> k >> m;
    db(n, k, m);
    vector<int> deled(n, true);
    for (size_t i = 0; i < m; i++)
    {
        int x;
        cin >> x;
        deled[x - 1] = 0;
    }
    db(deled);
    if ((n - m) % (k - 1))
    {
        cout << "NO\n";
        return;
    }
    int t = (n - m) / (k - 1);
    int l = 0, r = n - m;
    db(t);
    for (int i = 0; i < n; i++)
    {
        if (!deled[i])
        {
            db(i, l, r);
            int sumofx = l - (k - 1) / 2;
            db(0, sumofx, (t - 1) * (k - 1));
            if (0 <= sumofx && sumofx <= (t - 1) * (k - 1))
            {
                int rhs = r - (t - 1) * (k - 1) + sumofx;
                db(rhs, (k - 1) / 2);
                if (rhs == (k - 1) / 2)
                {
                    cout << "YES\n";
                    return;
                }
            }
        }
        else
            ++l, --r;
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
        solveCase();
    return 0;
}