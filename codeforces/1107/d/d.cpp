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
    int n = 5040;
    cin >> n;
    vector<int> divisors;
    for (size_t i = 1; i <= n; i++)
        if (n % i == 0)
            divisors.pb(i);
    vector<vector<int>> a(n + 10, vector<int>(n + 10));
    for (size_t i = 1; i <= n; i++)
    {
        string str;
        cin >> str;
        for (int j = 1; j <= n; j += 4)
        {
            char x = str[(j - 1) / 4];
            if (x >= 'A')
                x = 10 + x - 'A';
            else
                x = x - '0';
            // char x = 15;
            int rptr = j + 3;
            while (rptr >= j)
            {
                a[i][rptr] = x & 1;
                x /= 2;
                --rptr;
            }
        }
        db(i, a[i]);
    }
    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= n; j++)
        {
            a[i][j] += a[i - 1][j];
            a[i][j] += a[i][j - 1];
            a[i][j] -= a[i - 1][j - 1];
        }
        // db(i, a[i]);
    }
    auto sum = [&](int r1, int c1, int r2, int c2) -> int
    {
        return a[r2][c2] - a[r1 - 1][c2] - a[r2][c1 - 1] + a[r1 - 1][c1 - 1];
    };
    db(divisors);
    auto check = [&](int idx) -> bool
    {
        db(idx);
        int x = divisors[idx];
        db(x);
        for (size_t i = 1; i <= n; i += x)
            for (size_t j = 1; j <= n; j += x)
            {
                int s = sum(i, j, i + x - 1, j + x - 1);
                if (s == 0 || s == (x * x))
                    continue;
                db(i, j, x, s);
                return false;
            }
        db(x, "yes");
        return true;
    };
    int low = 0, high = divisors.size() - 1;
    int ans = 0;
    while (low <= high)
    {
        if (check(low))
            ans = low;
        ++low;
    }
    cout << divisors[ans] << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    srand(time(NULL));
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}