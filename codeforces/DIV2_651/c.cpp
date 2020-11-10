#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
using ll = long long;
const int NAX = 1e9 + 5, MOD = 1000000007;
const int NAX2 = sqrt(NAX) + 100;

vector<int> dp(NAX2);

void out(bool ok)
{
    if (ok)
        cout << "Ashishgup\n";
    else
        cout << "FastestFinger\n";
}

bool check(int x, int depth = 0)
{
    if (x <= 1)
        return false;
    if (depth == 10)
        return false;
    for (ll i = 1; i * i <= x; i++)
    {
        if (x % i)
            continue;
        if (i != 1)
            if (i & 1)
                if (!check(x / i, depth + 1))
                    return true;
        if ((x / i) & 1)
            if (!check(i, depth + 1))
                return true;
    }
    return !check(x - 1, depth + 1);
}

void solveCase()
{
    dp[1] = false;
    for (int i = 2; i < NAX2; i++)
    {
        if (!dp[i])
            dp[i] = !dp[i - 1];
        if (!dp[i])
            for (int j = 2 * i; j < NAX2; j += i)
                if (!dp[j])
                    dp[j] = !dp[i];
    }
    int t;
    cin >> t;
    for (size_t i = 0; i < t; i++)
    {
        int x;
        cin >> x;
        db(x);
        out(check(x));
    }
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